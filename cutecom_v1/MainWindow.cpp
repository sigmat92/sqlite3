#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ConfigManager.h"
#include "Logger.h"
#include "LogViewer.h"

#include <QSerialPortInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), serial(new QSerialPort(this)),
      config(new ConfigManager(this)), logger(new Logger(this)) {
    ui->setupUi(this);

    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
        ui->portComboBox->addItem(info.portName());

    ui->baudRateBox->addItems({ "9600", "19200", "38400", "57600", "115200" });

    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::openOrCloseSerial);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendData);
    connect(ui->loadConfigButton, &QPushButton::clicked, this, &MainWindow::loadConfig);
    connect(ui->saveConfigButton, &QPushButton::clicked, this, &MainWindow::saveConfig);
    connect(ui->viewLogButton, &QPushButton::clicked, this, &MainWindow::showLogViewer);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);

    logger->init("serial_log.db");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadConfig() {
    config->load("config.json", this);
}

void MainWindow::saveConfig() {
    config->save("config.json", this);
}

void MainWindow::openOrCloseSerial() {
    if (serial->isOpen()) {
        serial->close();
        ui->connectButton->setText("Connect");
    } else {
        serial->setPortName(ui->portComboBox->currentText());
        serial->setBaudRate(ui->baudRateBox->currentText().toInt());
        if (serial->open(QIODevice::ReadWrite)) {
            ui->connectButton->setText("Disconnect");
        } else {
            QMessageBox::warning(this, "Error", serial->errorString());
        }
    }
}

void MainWindow::sendData() {
    const QString msg = ui->sendEdit->text();
    serial->write(msg.toUtf8());
    ui->terminalText->append("TX: " + msg);
    logger->log("TX", msg);
}

void MainWindow::readData() {
    const QString msg = QString::fromUtf8(serial->readAll());
    ui->terminalText->append("RX: " + msg);
    logger->log("RX", msg);
}

void MainWindow::showLogViewer() {
    LogViewer *viewer = new LogViewer(this);
    viewer->loadLog("serial_log.db");
    viewer->setAttribute(Qt::WA_DeleteOnClose);
    viewer->show();
}

