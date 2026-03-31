#include <QApplication>
#include <QDebug>

#include "view/homeview.h"
#include "controller/homecontroller.h"

#include "service/vitalsservice.h"
#include "service/sessionservice.h"
#include "service/settingsservice.h"

#include "storage/patientrepository.h"
#include "storage/databasemanager.h"

#include "model/vitalsmodel.h"
#include "platform/uart/uartdevice.h"
#include "platform/uart/protocolparser.h"
#include "view/settingsview.h"

#include <QDir>
#include <QStringList>
#include "view/printview.h"

#include <QStackedWidget>

#include "view/recordsview.h"

#include "storage/vitalsrepository.h"

#include "storage/record.h"

#include <vector>

#include <sqlite3.h>

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

    // ---------- VIEW ----------
    HomeView* homeView = new HomeView;
    RecordsView *recordsView = new RecordsView;
    PrintView   *printView   = new PrintView;
        
    QStackedWidget *stackedWidget = new QStackedWidget;

    stackedWidget->addWidget(homeView);     
    stackedWidget->addWidget(printView);
    stackedWidget->addWidget(recordsView);

    //stackedWidget->setCurrentWidget(homeView);
    //stackedWidget->showFullScreen();
    
    // ---------- MODEL ----------
    VitalsModel* vitalsModel = new VitalsModel(&app);

    // ---------- SERVICES ----------

    VitalsService* vitalsService = new VitalsService(&app);
    SessionService* sessionService = new SessionService(&app);
    PatientRepository* patientRepo = new PatientRepository();
    VitalsRepository* repo = new VitalsRepository();

    vitalsService->setRepository(repo);

// SESSION CREATION (ONLY ONCE)


QObject::connect(homeView,
    &HomeView::startSessionRequested,
    [=](QString name,int age,QString mobile,QString gender)
{
    if(vitalsService->sessionId() > 0)
    {
        qDebug()<<"Session already active";
        return;
    }

    int patientId = patientRepo->savePatient(name,age,mobile,gender);
    if(patientId<=0) return;

    int sessionId = sessionService->createSession(patientId);
    repo->createEmptyVitals(sessionId);

    if(sessionId<=0) return;

    qDebug()<<"Session created:"<<sessionId;

    vitalsService->setSessionId(sessionId);
    homeView->setCurrentSessionId(sessionId);   // IMPORTANT
});
//Print requested
    //RecordsView *recordsView = new RecordsView;
    //PrintView   *printView   = new PrintView;

    //QStackedWidget *stackedWidget = new QStackedWidget;

    //stackedWidget->addWidget(recordsView);
    //stackedWidget->addWidget(printView);

QObject::connect(homeView, &HomeView::startPrintingRequested,
                 [&](int sessionId){

    qDebug() << "Printing current session:" << sessionId;

    QVariantMap data = repo->getLatestVitals(sessionId);

    printView->setData(data);

    stackedWidget->setCurrentWidget(printView);
    stackedWidget->showFullScreen();
    homeView->hide();
});

QObject::connect(printView, &PrintView::exitRequested,
                 [&](){

    stackedWidget->setCurrentWidget(homeView);
});
//
// -------- LOAD RECORDS --------
std::vector<Record> records = getAllSessions();   // 
recordsView->setData(records);

// -------- RECORD SELECTION --------
QObject::connect(recordsView, &RecordsView::recordSelected,
                 [=](int sessionId){

    qDebug() << "Selected session:" << sessionId;

    QVariantMap data =
                    repo->getLatestVitals(sessionId);
       
    printView->setData(data);

    stackedWidget->setCurrentWidget(printView);
});
//back from printview
QObject::connect(printView, &PrintView::backRequested,
        [&](){

    stackedWidget->setCurrentWidget(recordsView);
    stackedWidget->showFullScreen();
});
// RESET SESSION
QObject::connect(homeView,
    &HomeView::resetSessionRequested,
    [=]()
{
    qDebug()<<"Reset session";
    vitalsService->setSessionId(-1);
});


// ---------- UART ----------
UartDevice* uart = new UartDevice(&app);

QStringList ports = {
    "/dev/ttyACM0",
    "/dev/ttyACM1"
};

for (const auto& dev : ports)
{
    qDebug() << "Trying UART:" << dev;

    if (uart->open(dev.toStdString().c_str(),9600))
    {
        qDebug() << "UART connected:" << dev;
        break;
    }
}

// ---------- PROTOCOL ----------
    ProtocolParser* parser = new ProtocolParser(&app);

    // ---------- CONNECT Protocol → Service ----------
    // UART → Parser
    QObject::connect(uart,&UartDevice::bytesReceived,
            parser,&ProtocolParser::feed);

    // Parser → Service
    QObject::connect(parser,&ProtocolParser::temperatureReceived,
            vitalsService,&VitalsService::onTemperature);

    QObject::connect(parser,&ProtocolParser::spo2Received,
            vitalsService,&VitalsService::onSpo2);

    QObject::connect(parser,&ProtocolParser::nibpReceived,
            vitalsService,&VitalsService::onNibp);

    QObject::connect(parser,&ProtocolParser::weightReceived,
            vitalsService,&VitalsService::onWeight);

    QObject::connect(parser,&ProtocolParser::heightReceived,
            vitalsService,&VitalsService::onHeight);

    // Service → UART
    QObject::connect(vitalsService,&VitalsService::sendCommand,
            uart,&UartDevice::send);

    // Service → Model
        
    QObject::connect(vitalsService,&VitalsService::temperatureReady,
            vitalsModel,&VitalsModel::setTemperature);

    QObject::connect(vitalsService,&VitalsService::spo2Ready,
            vitalsModel,&VitalsModel::setSpO2);

    QObject::connect(vitalsService,&VitalsService::nibpReady,
            vitalsModel,&VitalsModel::setNIBP);

    QObject::connect(vitalsService,&VitalsService::weightReady,
            vitalsModel,&VitalsModel::setWeight);

    QObject::connect(vitalsService,&VitalsService::heightReady,
            vitalsModel,&VitalsModel::setHeight);
    
    // ---------- HOME CONTROLLER ----------
    new HomeController(homeView,
                   sessionService,
                   patientRepo,
                   vitalsModel,
                   vitalsService,   
                   nullptr,
                   &app);
    // ---------- SETTINGS VIEW ----------
SettingsView* settingsView = new SettingsView;

// Home → Settings
QObject::connect(homeView,
                 &HomeView::settingsRequested,
                 [=]() {
                     homeView->hide();
                     settingsView->showFullScreen();
                 });

// Settings → Home
QObject::connect(settingsView,
                 &SettingsView::exitRequested,
                 [=]() {
                     settingsView->hide();
                     homeView->showFullScreen();
                 });


    //homeView->showFullScreen();
    stackedWidget->setCurrentWidget(homeView);
    stackedWidget->showFullScreen();
    
    return app.exec();
}
