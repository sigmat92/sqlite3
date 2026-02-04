#include <QApplication>
#include "view/mainwindow.h"
#include "controller/cameracontroller.h"
#include "controller/barcodescanner.h"
#include "model/barcodemodel.h"
#include "storage/sqliterecorder.h"

#include "view/homeview.h"
#include "controller/homecontroller.h"
#include "service/sessionservice.h"
#include "storage/patientrepository.h"
#include "storage/sqliterecorder.h"
#include "controller/protocolcontroller.h"
//#include "uart/uartdevice.h"
#include "controller/protocolparser.h"
#include "model/vitalsmodel.h"
#include <QObject>

int main(int argc, char *argv[])
{
	
    qputenv("QT_QPA_PLATFORM", "wayland");   // or "eglfs" if no compositor
    qputenv("QT_OPENGL", "software");        // 
    qputenv("QT_QUICK_BACKEND", "software"); // safety
    
    QApplication app(argc, argv);

    //UartDevice* uart = new UartDevice(&app);
    /* ---------- UI ---------- */
    HomeView* view = new HomeView;
    //view->show();

    /* ---------- Models ---------- */
    VitalsModel* vitals = new VitalsModel(&app);

    /* ---------- Services ---------- */
    SessionService* session = new SessionService(&app);
    PatientRepository* repo = new PatientRepository(&app);

    /* ---------- UART / Protocol ---------- */
    UartDevice* uart = new UartDevice(&app);
    uart->open("/dev/ttyACM0", 9600);

    ProtocolParser* parser = new ProtocolParser(&app);

    ProtocolController* protocolCtrl =
        new ProtocolController(uart, parser, vitals, &app);

    /* ---------- Controllers ---------- */
    new HomeController(
        view,
        session,
        repo,
        vitals,
        protocolCtrl,
        &app
    );

    view->show();
    //view.showFullScreen();
    return app.exec();
}
    //QApplication app(argc, argv);

    //MainWindow win;

    /* Working Camera QR Scanner Code - Uncomment to enable
    BarcodeModel model;
    SQLiteRecorder db("barcodes.db");

    CameraController camera("/dev/video0");
    BarcodeScanner scanner;

    QObject::connect(&camera, &CameraController::frameColorReady,
                     &win, &MainWindow::updateFrame);

    QObject::connect(&camera, &CameraController::frameGrayReady,
                     &scanner, &BarcodeScanner::onFrame);

    QObject::connect(&scanner, &BarcodeScanner::barcodeDetected,
                     &model, &BarcodeModel::setBarcode);

    QObject::connect(&model, &BarcodeModel::barcodeChanged, [&]() {
        win.updateBarcode(model.text(), model.format());
        db.store(model.text(), model.format());
    });

    camera.start();
    win.show();

    int ret = app.exec();

    camera.stop();
    camera.wait();
    */
    //win.show();
    //return app.exec();
//}

