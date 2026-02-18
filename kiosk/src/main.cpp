#include <QApplication>
#include <QObject>

#include "view/homeview.h"
#include "controller/homecontroller.h"

#include "service/vitalsservice.h"
#include "service/sessionservice.h"

#include "storage/patientrepository.h"
#include "storage/sqliterecorder.h"

#include "controller/protocolcontroller.h"
#include "controller/protocolparser.h"
#include "model/vitalsmodel.h"
#include "platform/uart/uartdevice.h"

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "wayland");
    qputenv("QT_OPENGL", "software");
    qputenv("QT_QUICK_BACKEND", "software");

    QApplication app(argc, argv);

    /* ---------- UI ---------- */
    HomeView* view = new HomeView;

    /* ---------- Model ---------- */
    VitalsModel* vitals = new VitalsModel(&app);

    /* ---------- Services ---------- */
    VitalsService* service = new VitalsService(&app);
    SessionService* session = new SessionService(&app);
    PatientRepository* repo = new PatientRepository(&app);

    /* ---------- UART / Protocol ---------- */
    UartDevice* uart = new UartDevice(&app);
    uart->open("/dev/ttyACM0", 9600);

    ProtocolParser* parser = new ProtocolParser(&app);

    ProtocolController* protocolCtrl =
        new ProtocolController(uart, parser, &app);

    /* ---------- Controllers ---------- */
    new HomeController(
        view,
        session,
        repo,
        vitals,
        protocolCtrl,
        &app
    );

    /* ---------- Protocol → Service ---------- */
    QObject::connect(protocolCtrl, &ProtocolController::temperatureRaw,
                     service, &VitalsService::onTemperatureRaw);

    QObject::connect(protocolCtrl, &ProtocolController::spo2Raw,
                     service, &VitalsService::onSpO2Raw);

    QObject::connect(protocolCtrl, &ProtocolController::weightRaw,
                     service, &VitalsService::onWeightRaw);

    QObject::connect(protocolCtrl, &ProtocolController::heightRaw,
                     service, &VitalsService::onHeightRaw);

    QObject::connect(protocolCtrl, &ProtocolController::nibpRaw,
                     service, &VitalsService::onNibpRaw);

    /* ---------- Service → Model ---------- */
    QObject::connect(service, &VitalsService::temperatureReady,
                     vitals, &VitalsModel::setTemperature);

    QObject::connect(service, &VitalsService::spo2Ready,
                     vitals, &VitalsModel::setSpO2);

    QObject::connect(service, &VitalsService::weightReady,
                     vitals, &VitalsModel::setWeight);

    QObject::connect(service, &VitalsService::heightReady,
                     vitals, &VitalsModel::setHeight);

    QObject::connect(service, &VitalsService::nibpReady,
                     vitals, &VitalsModel::setNIBP);

    view->show();
    return app.exec();
}

