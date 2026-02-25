#include <QApplication>
#include <QDebug>

#include "view/homeview.h"
#include "controller/homecontroller.h"

#include "service/vitalsservice.h"
#include "service/sessionservice.h"
#include "service/settingsservice.h"

#include "storage/patientrepository.h"
#include "storage/databasemanager.h"

#include "controller/protocolcontroller.h"
#include "controller/protocolparser.h"
#include "model/vitalsmodel.h"
#include "platform/uart/uartdevice.h"

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
    PatientRepository* patientRepo = new PatientRepository;

    // ---------- UART ----------
    UartDevice* uart = new UartDevice(&app);
    uart->open("/dev/ttyACM0", 9600);

    ProtocolParser* parser = new ProtocolParser(&app);

    ProtocolController* protocolCtrl =
        new ProtocolController(uart, parser, &app);

    // ---------- CONNECT Protocol → Service ----------
    QObject::connect(protocolCtrl, &ProtocolController::temperatureRaw,
                     vitalsService, &VitalsService::onTemperatureRaw);

    QObject::connect(protocolCtrl, &ProtocolController::spo2Raw,
                     vitalsService, &VitalsService::onSpO2Raw);

    QObject::connect(protocolCtrl, &ProtocolController::weightRaw,
                     vitalsService, &VitalsService::onWeightRaw);

    QObject::connect(protocolCtrl, &ProtocolController::heightRaw,
                     vitalsService, &VitalsService::onHeightRaw);

    QObject::connect(protocolCtrl, &ProtocolController::nibpRaw,
                     vitalsService, &VitalsService::onNibpRaw);

    // ---------- CONNECT Service → Model ----------
    QObject::connect(vitalsService, &VitalsService::temperatureReady,
                     vitalsModel, &VitalsModel::setTemperature);

    QObject::connect(vitalsService, &VitalsService::spo2Ready,
                     vitalsModel, &VitalsModel::setSpO2);

    QObject::connect(vitalsService, &VitalsService::weightReady,
                     vitalsModel, &VitalsModel::setWeight);

    QObject::connect(vitalsService, &VitalsService::heightReady,
                     vitalsModel, &VitalsModel::setHeight);

    QObject::connect(vitalsService, &VitalsService::nibpReady,
                     vitalsModel, &VitalsModel::setNIBP);

    // ---------- HOME CONTROLLER ----------
    new HomeController(homeView,
                       sessionService,
                       patientRepo,
                       vitalsModel,
                       protocolCtrl,   
                       nullptr,
                       &app);

    homeView->show();

    return app.exec();
}
