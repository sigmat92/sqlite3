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


/*
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
    SQLiteRecorder db("barcodes.db");   // ✅ CREATE DB HERE

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
        db.store(model.text(), model.format());   // ✅ NOW VALID
    });

    camera.start();
    win.show();

    int ret = app.exec();

    camera.stop();
    camera.wait();

    return ret;
}



#include <QApplication>
#include "view/mainwindow.h"
#include "controller/cameracontroller.h"
#include "controller/barcodescanner.h"
#include "model/barcodemodel.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow win;
    BarcodeModel model;
    BarcodeScanner scanner(&model);
    CameraController camera;

    QObject::connect(&camera, &CameraController::frameReady,
                     &win, &MainWindow::updateFrame);

    QObject::connect(&camera, &CameraController::grayFrameReady,
                     &scanner, &BarcodeScanner::onGrayFrame);

    QObject::connect(&model, &BarcodeModel::barcodeChanged, [&]() {
    win.updateBarcode(model.text(), model.format());
    db.store(model.text(), model.format());
});
//added
    win.show();
    camera.start();

    int ret = app.exec();
    camera.stop();
    return ret;
}


#include <QApplication>
#include "controller/cameracontroller.h"
#include "controller/barcodescanner.h"
#include "model/barcodemodel.h"
#include "storage/sqliterecorder.h"
#include "view/mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    BarcodeModel model;
    BarcodeScanner scanner(&model);
    SQLiteRecorder db("/tmp/scans.db");

    CameraController camera;
    MainWindow win;

    QObject::connect(&camera, &CameraController::frameReady,
                     &scanner, &BarcodeScanner::onFrame);

    QObject::connect(&camera, &CameraController::frameReady,
                     &win, &MainWindow::updateFrame);

    QObject::connect(&model, &BarcodeModel::barcodeUpdated,
                     [&]() {
                         db.store(model.text(), model.format());
                     });

    win.show();
    camera.start();

    return app.exec();
}
*/
