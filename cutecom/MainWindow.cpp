#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ConfigManager.h"

#include <QFileDialog>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial(new QSerialPort(this))
    , config(new ConfigManager(this))
{
    ui->setupUi(this);

    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        ui->portComboBox->addItem(info.portName());
    }

    ui->baudRateBox->addItems({"9600", "19200", "38400", "57600", "115200"});

    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::openOrCloseSerial);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendData);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(ui->loadConfigButton, &QPushButton::clicked, this, &MainWindow::loadConfig);
    connect(ui->saveConfigButton, &QPushButton::clicked, this, &MainWindow::saveConfig);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openOrCloseSerial() {
    if (serial->isOpen()) {
        serial->close();
        ui->connectButton->setText("Connect");
        ui->statusbar->showMessage("Serial port closed");
        return;
    }

    serial->setPortName(ui->portComboBox->currentText());
    serial->setBaudRate(ui->baudRateBox->currentText().toInt());

    if (serial->open(QIODevice::ReadWrite)) {
        ui->connectButton->setText("Disconnect");
        ui->statusbar->showMessage("Serial port opened");
    } else {
        ui->statusbar->showMessage("Failed to open serial port");
    }
}

void MainWindow::sendData() {
    if (serial->isOpen()) {
        QByteArray data = ui->sendEdit->text().toUtf8();
        serial->write(data);
        ui->terminalText->append("[TX] " + data);
    }
}

void MainWindow::readData() {
    QByteArray data = serial->readAll();
    ui->terminalText->append("[RX] " + QString::fromUtf8(data));
}

void MainWindow::loadConfig() {
    QString path = QFileDialog::getOpenFileName(this, "Load Config", "", "*.json");
    if (!path.isEmpty()) {
        config->load(path, this);
        ui->statusbar->showMessage("Config loaded");
    }
}

void MainWindow::saveConfig() {
    QString path = QFileDialog::getSaveFileName(this, "Save Config", "", "*.json");
    if (!path.isEmpty()) {
        config->save(path, this);
        ui->statusbar->showMessage("Config saved");
    }
}