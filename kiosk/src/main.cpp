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

int main(int argc, char *argv[])
{
	
    qputenv("QT_QPA_PLATFORM", "wayland");   // or "eglfs" if no compositor
    qputenv("QT_OPENGL", "software");        // 🔥 critical
    qputenv("QT_QUICK_BACKEND", "software"); // safety
    QApplication app(argc, argv);

    SQLiteRecorder db("patients.db");
    PatientRepository repo(&db);
    SessionService session;
    //auto* encoder = new EncoderService("/dev/input/event2");
    //encoder->start();


    HomeView view;
    HomeController controller(&view, &session, &repo);
    view.show();
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

