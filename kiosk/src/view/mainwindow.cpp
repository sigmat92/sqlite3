#include "mainwindow.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>

#include <QHBoxLayout>
#include <QFrame>
#include <QSpacerItem>

#include "model/qrgenerator.h"
#include "controller/printcontroller.h"
#include "platform/uart/uartdevice.h"
#include "controller/protocolparser.h"
#include "controller/protocolcontroller.h"
#include "model/vitalsmodel.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      uart(new UartDevice(this)),
      parser(new ProtocolParser(this)),
      vitals(new VitalsModel(this)),
      protocol(new ProtocolController(uart, parser, vitals, this))
{
    uart->open("/dev/ttyACM0",9600);
/*
    connect(vitals, &VitalsModel::temperatureChanged,
            this, &MainWindow::onTemperature);

    connect(vitals, &VitalsModel::spo2Changed,
            this, &MainWindow::onSpo2);
*/
    protocol->start();
   //temp read control button 
//connect(tempBtn, &QPushButton::clicked,
//        this, &MainWindow::onReadTemperature);

    // Setup UI
    setStyleSheet(R"(
                QMainWindow {
                    background-color: #121212;
                    color: #ffffff;
                }
                QLineEdit {
                    border-radius: 6px;
                    padding: 6px;
                    font-size: 16px;
                }
                QPushButton {
                    background-color: #2d89ef;
                    border-radius: 6px;
                    font-size: 15px;
                    color: white;
                }
                QPushButton:hover {
                    background-color: #1b5fbf;
                }
                QPushButton:pressed {
                    background-color: #144a96;
                }
                )");

/* ---------- CENTRAL WIDGET ---------- */

QWidget* central = new QWidget(this);
setCentralWidget(central);

QVBoxLayout* mainLayout = new QVBoxLayout(central);
mainLayout->setContentsMargins(10, 10, 10, 10);
mainLayout->setSpacing(8);

/* ---------- CAMERA PREVIEW ---------- */

QFrame* previewFrame = new QFrame;
previewFrame->setMinimumHeight(360);
previewFrame->setFrameShape(QFrame::StyledPanel);
mainLayout->addWidget(previewFrame, 1);  

/* ---------- CONTROL BAR ---------- */

QFrame* controlBar = new QFrame;
controlBar->setFixedHeight(160);
controlBar->setStyleSheet(
    "QFrame { background-color: #1e1e1e; border-radius: 10px; }"
);
mainLayout->addWidget(controlBar);

/* ---------- CONTROL BAR LAYOUT ---------- */

QHBoxLayout* barLayout = new QHBoxLayout(controlBar);
barLayout->setContentsMargins(12, 12, 12, 12);
barLayout->setSpacing(10);

/* ---------- INPUT FIELD ---------- */

inputEdit = new QLineEdit;
inputEdit->setPlaceholderText("Scanned / Enter text");
inputEdit->setMinimumHeight(40);

/* ---------- BUTTONS ---------- */

generateBtn = new QPushButton("Generate QR");
printBtn    = new QPushButton("Print QR");
scanBtn     = new QPushButton("Start Scanner");
tempBtn     = new QPushButton("Read Temp");

for (auto btn : {generateBtn, printBtn, scanBtn, tempBtn}) {
    btn->setMinimumHeight(40);
    btn->setMinimumWidth(140);
}

/* ---------- QR PREVIEW ---------- */

qrLabel = new QLabel;
//qrLabel->setFixedSize(96, 96);
qrLabel->setFixedSize(120, 120);
qrLabel->setStyleSheet(
    "QLabel { background:#fff; border-radius:6px; }"
);
qrLabel->setAlignment(Qt::AlignCenter);

/* ---------- TEMP LABEL ---------- */

tempLabel = new QLabel("--.- °F");
tempLabel->setAlignment(Qt::AlignCenter);
tempLabel->setMinimumWidth(120);
tempLabel->setStyleSheet(
    "QLabel { background:#000; color:#00ffcc; "
    "font-size:32px; border-radius:6px; padding:6px; }"
);

/* ---------- ASSEMBLE BAR ---------- */

barLayout->addWidget(tempLabel);
barLayout->addWidget(qrLabel);
barLayout->addWidget(inputEdit, 1);
barLayout->addWidget(generateBtn);
barLayout->addWidget(printBtn);
barLayout->addWidget(scanBtn);
barLayout->addWidget(tempBtn);

    connect(generateBtn, &QPushButton::clicked,
            this, &MainWindow::onGenerateQR);

    connect(printBtn, &QPushButton::clicked,
            this, &MainWindow::onPrintQR);

/* -----add scanner logic ---------- */
/* ---- create backend objects ---- */

camera  = new CameraController("/dev/video0", 640, 480, this);
scanner = new BarcodeScanner(this);
model   = new BarcodeModel(this);
db      = new SQLiteRecorder("barcodes.db", this);

/* ---- UI ---- */

/* ---- connections (SAME AS WORKING CODE) ---- */

// Preview

connect(camera, &CameraController::frameColorReady,
        this, &MainWindow::updateFrame);

// Grayscale -> scanner

connect(camera, &CameraController::frameGrayReady,
        scanner, &BarcodeScanner::onFrame);

// Scanner -> model

connect(scanner, &BarcodeScanner::barcodeDetected,
        model, &BarcodeModel::setBarcode);

// Model -> UI + DB

connect(model, &BarcodeModel::barcodeChanged, this, [this]() {
    updateBarcode(model->text(), model->format());
    db->store(model->text(), model->format());
});
//temp button logic
connect(tempBtn, &QPushButton::clicked, this, [this]() {
    tempLabel->setText("Reading...");
    protocol->requestTemperature();
});

/* -----scanner button toggle logic ----- */

connect(scanBtn, &QPushButton::clicked, this, [this]() {

    if (!scannerRunning) {

        /* ---- CREATE CAMERA FRESH ---- */
        
        camera = new CameraController("/dev/video0", 640, 480, this);

        connect(camera, &CameraController::frameColorReady,
                this, &MainWindow::updateFrame);

        connect(camera, &CameraController::frameGrayReady,
                scanner, &BarcodeScanner::onFrame);

        camera->start();

        scanBtn->setText("Stop Scanner");
        //scanBtn->setText("Done...");
        scannerRunning = true;
        //scannerRunning = false;

    } else {
    //if (scannerRunning) {

        /* ---- STOP & DESTROY CAMERA ---- */
        scannerRunning = false;
        //scannerRunning = true;
        camera->stop();
        camera->wait();     // VERY IMPORTANT
        camera->deleteLater();
        camera = nullptr;
        update(); 
        scanBtn->setText("Start Scanner");
        resetUI();

    }

});

}

//Constructor end

/* ------ vitals update ------ */
/*
void MainWindow::onReadTemperature()
{
    tempLabel->setText("Reading...");
    protocol->requestTemperature();   // clean API
}
*/

void MainWindow::onTemperature(float value)
{
    if (!tempLabel)
        return;

    tempLabel->setText(
        QString::number(value, 'f', 1) + " °F"
    );
}

void MainWindow::onSpo2(int value)
{
    //ui->lblSpo2->setText(
    //    QString::number(value) + " %"
    //);
}

//vitals end

/* ---------- QR GENERATION ---------- */

void MainWindow::onGenerateQR()
{
    QString text = inputEdit->text();
    if (text.isEmpty())
        return;

    currentQR = QRGenerator::generate(text, 256);
    update();   
}

/*----- update baercode into ui ---- */

void MainWindow::updateBarcode(const QString& text,
                               const QString& format)
{
    if (!scannerRunning)
        return;

    inputEdit->setText(text);
    currentQR = QRGenerator::generate(text, 256);
    qrLabel->setPixmap(QPixmap::fromImage(currentQR));
}

/* ---------- PRINT QR ---------- */

void MainWindow::onPrintQR()
{
    if (currentQR.isNull())
        return;

    PrinterController::printQR(currentQR, m_text);
}

/* ---------- CAMERA FRAME UPDATE ---------- */

void MainWindow::updateFrame(const QImage& img)
{
    if (!scannerRunning || img.isNull())
        return;

    m_frame = img;
    update();
}

/* ---------- PAINT EVENT (CAMERA PREVIEW) ---------- */

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    // Preview area = window minus control bar

    QRect previewRect = centralWidget()->geometry();
    previewRect.setBottom(previewRect.bottom() - 140);

    p.fillRect(previewRect, Qt::black);

    /* ---------- SCANNER ON → CAMERA PREVIEW ---------- */

    if (scannerRunning && !m_frame.isNull()) {

        QImage scaled = m_frame.scaled(
            previewRect.size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        );

        QPoint center = previewRect.center() -
                        QPoint(scaled.width()/2, scaled.height()/2);

        p.drawImage(center, scaled);
        return;
    }

    /* ---------- SCANNER OFF → SHOW QR ---------- */

    if (!scannerRunning && !currentQR.isNull()) {

        int size = qMin(previewRect.width(),
                        previewRect.height()) * 0.7;

        QImage scaledQR = currentQR.scaled(
            size, size,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        );

        QPoint center = previewRect.center() -
                        QPoint(scaledQR.width()/2, scaledQR.height()/2);

        p.drawImage(center, scaledQR);
        return;
    }

    /* ---------- IDLE STATE ---------- */

    p.setPen(Qt::gray);
    p.setFont(QFont("Sans", 18));
    p.drawText(previewRect,
               Qt::AlignCenter,
               "Ready");
}

void MainWindow::resetUI()
{
    // Clear preview frame
    m_frame = QImage();
    update();   // repaint window

    // Clear barcode text
    inputEdit->clear();

    // Clear QR image
    currentQR = QImage();
    qrLabel->clear();

    // Optional: reset status labels if any
    // statusLabel->setText("Ready");

    m_text.clear();
    m_format.clear();
}


