#pragma once
#include <QMainWindow>
#include <QImage>
#include <QString>
#include "controller/cameracontroller.h"
#include "controller/barcodescanner.h"
#include "model/barcodemodel.h"
#include "storage/sqliterecorder.h"

#include "platform/uart/uartdevice.h"
#include "controller/protocolparser.h"
#include "controller/protocolcontroller.h"
#include "model/vitalsmodel.h"


class QLabel;
class QLineEdit;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

public slots:
    void onGenerateQR();
    void onPrintQR();
    void updateFrame(const QImage& img);
    void updateBarcode(const QString& text, const QString& format);
    //void onTemperature(float value);
    //void onSpo2(int value);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    void onTemperature(float value);
    void onSpo2(int value);
    void resetUI();

    QPushButton *tempBtn;
    QLabel *tempLabel;

    UartDevice *uart;
    ProtocolParser *parser;
    VitalsModel *vitals;
    ProtocolController *protocol;

    QImage  m_frame;
    QString m_text;
    QString m_format;
    QImage currentQR;
    QLineEdit* inputEdit;
    QLabel* qrLabel;
    QPushButton* generateBtn;
    QPushButton* printBtn;
    CameraController* camera;
    BarcodeScanner*  scanner;
    BarcodeModel*    model;
    SQLiteRecorder*  db;
    QPushButton* scanBtn;
    bool scannerRunning = false;

};



