#include <QApplication>
#include <QDebug>

#include "view/homeview.h"
#include "view/settingsview.h"
#include "view/printview.h"
#include "view/recordsview.h"
#include "view/visiontestview.h"

#include "controller/homecontroller.h"
#include "controller/settingscontroller.h"
#include "controller/visiontestcontroller.h"

#include "service/vitalsservice.h"
#include "service/visionservice.h"
#include "service/sessionservice.h"

#include "storage/patientrepository.h"
#include "storage/databasemanager.h"
#include "storage/vitalsrepository.h"
#include "storage/record.h"

#include "model/vitalsmodel.h"

#include "platform/uart/uartdevice.h"
#include "platform/uart/protocolparser.h"

#include "controller/navigationmanager.h"

#include <QStackedWidget>
#include <QStringList>
#include <vector>
#include <sqlite3.h>
#include "storage/sessionrepository.h"

#include "model/settingsmodel.h"
#include "service/settingsservice.h"
#include "service/syncservice.h"
#include "storage/settingsrepository.h"


/* ================= LOAD ALL SESSIONS ================= */

std::vector<Record> getAllSessions()
{
    std::vector<Record> records;

    sqlite3* db = DatabaseManager::instance().connection();
    sqlite3_stmt* stmt = nullptr;

    const char* sql = R"(
        SELECT 
            s.id,
            p.id,
            DATE(s.started_at),
            TIME(s.started_at),
            p.name
        FROM sessions s
        JOIN patients p ON s.patient_id = p.id
        JOIN vitals v ON v.session_id = s.id   
        GROUP BY s.id
        ORDER BY s.id DESC;
    )";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return records;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Record r;

        r.sessionId = sqlite3_column_int(stmt, 0);
        r.patientId = sqlite3_column_int(stmt, 1);
        r.date = QString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        r.time = QString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        r.name = QString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));

        records.push_back(r);
    }

    sqlite3_finalize(stmt);
    return records;
}

/* ================= MAIN ================= */

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "wayland");
    qputenv("QT_OPENGL", "software");

    QApplication app(argc, argv);

    // ---------- DATABASE ----------
    if (!DatabaseManager::instance().open("kiosk.db"))
    {
        qDebug() << "Database initialization failed";
        return -1;
    }

    // ---------- VIEWS ----------
    HomeView* homeView       = new HomeView;
    SettingsView* settingsView = new SettingsView;
    PrintView* printView     = new PrintView;
    RecordsView* recordsView = new RecordsView;
    VisionTestView* visionView = new VisionTestView;

    // ---------- STACK ----------
    QStackedWidget* stackedWidget = new QStackedWidget;

    // ---------- NAVIGATION ----------
    NavigationManager* nav = new NavigationManager(stackedWidget);

    nav->registerScreen(Screen::Home, homeView);
    nav->registerScreen(Screen::Settings, settingsView);
    nav->registerScreen(Screen::Print, printView);
    nav->registerScreen(Screen::Records, recordsView);
    nav->registerScreen(Screen::Vision, visionView);

    // ---------- MODEL ----------
    VitalsModel* vitalsModel = new VitalsModel(&app);

    // ---------- SERVICES ----------
    VitalsService* vitalsService = new VitalsService(&app);
    
    PatientRepository* patientRepo = new PatientRepository();
    VitalsRepository* repo = new VitalsRepository();

    vitalsService->setRepository(repo);

    SessionRepository* sessionRepo = new SessionRepository();

    SessionService* sessionService = new SessionService(sessionRepo, &app);

    // -------- DARK MODE --------
    
    SettingsRepository* settingsRepo = new SettingsRepository();
    SettingsModel* settingsModel = new SettingsModel(&app);
    SyncService* syncService = new SyncService();

    SettingsService* settingsService =
                                 new SettingsService(settingsModel, settingsRepo, &app);

            SettingsController* settingsController =
                                    new SettingsController(
                                        settingsView,
                                        settingsService,
                                        settingsRepo,
                                        //adminAuthService,
                                        vitalsService,
                                        syncService,
                                        &app);
    /*
    struct AppContext {
        SettingsModel* settingsModel;
        SettingsService* settingsService;
        SettingsRepository* settingsRepo;
        VitalsService* vitalsService;
        SyncService* syncService;
    };
    SettingsController(SettingsView* view, AppContext* ctx)
    */
  


    QString theme = settingsRepo->get("theme");

    if (theme == "dark")
    {
        settingsService->applyTheme(true);
    }
    else
    {
        settingsService->applyTheme(false);
    }

    // ---------- CONTROLLER ----------
  new HomeController(homeView,
                   sessionService,
                   patientRepo,
                   vitalsModel,
                   vitalsService,
                   repo,              // SAME INSTANCE
                   nullptr,
                   &app);
    VisionService* visionService = new VisionService(&app);

    new VisionTestController(
        visionView,
        visionService,
        &app
    );

    // ---------- RECORDS LOAD ----------
    recordsView->setData(getAllSessions());

    // ================= NAVIGATION =================

    // Home → Settings
    QObject::connect(homeView, &HomeView::settingsRequested,
                     [=]() {
                         nav->goTo(Screen::Settings);
                     });

    // Settings → Home
    QObject::connect(settingsView, &SettingsView::exitRequested,
                     [=]() {
                         nav->goBack();
                     });

    // Home → Print
    QObject::connect(homeView, &HomeView::startPrintingRequested,
                     [=](int sessionId){

        qDebug() << "Printing session:" << sessionId;

        QVariantMap data = repo->getLatestVitals(sessionId);
        printView->setData(data);

        nav->goTo(Screen::Print);
    });

    // Print → Home
    QObject::connect(printView, &PrintView::exitRequested,
                     [=]() {
                         nav->goTo(Screen::Home);
                     });

    // Print → Records
    QObject::connect(printView, &PrintView::backRequested,
                     [=]() {
                         recordsView->setData(getAllSessions());
                         nav->goTo(Screen::Records);
                     });

    // Records → Print
    QObject::connect(recordsView, &RecordsView::recordSelected,
                     [=](int sessionId){

        QVariantMap data = repo->getLatestVitals(sessionId);
        printView->setData(data);

        nav->goTo(Screen::Print);
    });

    // Home → Vision
    QObject::connect(homeView, &HomeView::visionTestRequested,
                     [=]() {
                         nav->goTo(Screen::Vision);
                     });

    // Vision → Back
    QObject::connect(visionView, &VisionTestView::exitRequested,
                     [=]() {
                         nav->goBack();
                     });
    // ---------- UART ----------
    UartDevice* uart = new UartDevice(&app);

    QStringList ports = { "/dev/ttyACM0", "/dev/ttyACM1" };

    for (const auto& dev : ports)
    {
        if (uart->open(dev.toStdString().c_str(), 9600))
        {
            qDebug() << "UART connected:" << dev;
            break;
        }
    }

    // ---------- PROTOCOL ----------
    ProtocolParser* parser = new ProtocolParser(&app);

    QObject::connect(uart, &UartDevice::bytesReceived,
                     parser, &ProtocolParser::feed);

    QObject::connect(parser, &ProtocolParser::temperatureReceived,
                     vitalsService, &VitalsService::onTemperature,
                    Qt::UniqueConnection); //

    QObject::connect(parser, &ProtocolParser::spo2Received,
                     vitalsService, &VitalsService::onSpo2);

    QObject::connect(parser, &ProtocolParser::nibpReceived,
                     vitalsService, &VitalsService::onNibp);

    QObject::connect(parser, &ProtocolParser::weightReceived,
                     vitalsService, &VitalsService::onWeight);

    QObject::connect(parser, &ProtocolParser::heightReceived,
                     vitalsService, &VitalsService::onHeight);

    QObject::connect(vitalsService, &VitalsService::sendCommand,
                     uart, &UartDevice::send);

    //QObject::connect(vitalsService, &VitalsService::temperatureReady,
    //                 vitalsModel, &VitalsModel::setTemperature);//
QObject::connect(vitalsService, &VitalsService::temperatureReady,
                 vitalsModel, &VitalsModel::setTemperature,
                 Qt::UniqueConnection);

    QObject::connect(vitalsService, &VitalsService::spo2Ready,
                     vitalsModel, &VitalsModel::setSpO2);

    QObject::connect(vitalsService, &VitalsService::nibpReady,
                     vitalsModel, &VitalsModel::setNIBP);

    QObject::connect(vitalsService, &VitalsService::weightReady,
                     vitalsModel, &VitalsModel::setWeight);

    QObject::connect(vitalsService, &VitalsService::heightReady,
                     vitalsModel, &VitalsModel::setHeight);

    // ---------- START ----------
    nav->goTo(Screen::Home);
    stackedWidget->showFullScreen();

    return app.exec();
}