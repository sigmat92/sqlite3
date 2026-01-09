#include <QApplication>

#include "view/mainwindow.h"
#include "controller/cameracontroller.h"
#include "controller/barcodescanner.h"
#include "model/barcodemodel.h"
#include "storage/sqliterecorder.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow win;
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

    return ret;
}

