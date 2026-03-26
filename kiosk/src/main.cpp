#include <QApplication>
#include <QDebug>

#include "view/homeview.h"
#include "controller/homecontroller.h"

#include "service/vitalsservice.h"
#include "service/sessionservice.h"
#include "service/settingsservice.h"

#include "storage/patientrepository.h"
#include "storage/databasemanager.h"

//#include "controller/protocolcontroller.h"
//#include "controller/protocolparser.h"

#include "model/vitalsmodel.h"
#include "platform/uart/uartdevice.h"
#include "platform/uart/protocolparser.h"
#include "view/settingsview.h"

#include <QDir>
#include <QStringList>

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
    if(sessionId<=0) return;

    qDebug()<<"Session created:"<<sessionId;

    vitalsService->setSessionId(sessionId);
});

// RESET SESSION
QObject::connect(homeView,
    &HomeView::resetSessionRequested,
    [=]()
{
    qDebug()<<"Reset session";
    vitalsService->setSessionId(-1);
});
    //VitalsService* vitalsService = new VitalsService(&app);
    //SessionService* sessionService = new SessionService(&app);
    //PatientRepository* patientRepo = new PatientRepository;

    //VitalsRepository* repo = new VitalsRepository();
    //    vitalsService->setRepository(repo);
    //    vitalsService->setSessionId(sessionId);  // 

/*
VitalsService* vitalsService = new VitalsService(&app);

SessionService* sessionService = new SessionService(&app);
PatientRepository* patientRepo = new PatientRepository();
VitalsRepository* repo = new VitalsRepository();
vitalsService->setRepository(repo);

QObject::connect(homeView,
    &HomeView::newSessionRequested,
    [=]()
{
    qDebug() << "Session reset";

    vitalsService->setSessionId(-1);

    static bool* sessionActivePtr = new bool(false);
    *sessionActivePtr = false;
});

QObject::connect(homeView,
    &HomeView::startSessionRequested,
    [=](QString name, int age, QString mobile, QString gender)
{
    static bool sessionActive = false;

    if(sessionActive)
    {
        qDebug() << "Session already active";
        return;
    }

    qDebug() << "SESSION SLOT TRIGGERED";

    if(name.isEmpty() || age <= 0 || gender.isEmpty())
    {
        qDebug() << "Invalid patient data";
        return;
    }

    int patientId = patientRepo->savePatient(name, age, mobile, gender);
    if(patientId <= 0) return;

    int sessionId = sessionService->createSession(patientId);
    if(sessionId <= 0) return;

    qDebug() << "Session created:" << sessionId;

    vitalsService->setSessionId(sessionId);

    sessionActive = true;   // 
});
*/
//hardcode
//int patientId = patientRepo->savePatient("test", 25, "9999999999", "Male");
//int sessionId = sessionService->createSession(patientId);

//VitalsRepository* repo = new VitalsRepository();

//vitalsService->setRepository(repo);
//vitalsService->setSessionId(sessionId);


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

    //ProtocolController* protocolCtrl =
    //    new ProtocolController(uart, parser, &app);

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


    homeView->showFullScreen();
    //homeView->show();
    return app.exec();
}
