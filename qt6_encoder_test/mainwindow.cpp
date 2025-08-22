#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , counter(0)
{
    ui->setupUi(this);

    rotary = new RotaryHandler("/dev/input/by-path/platform-rotary@0-event",
                               "/dev/input/by-path/platform-rotary-sw-event");
    rotary->moveToThread(&workerThread);

    connect(&workerThread, &QThread::started, rotary, &RotaryHandler::processEvents);
    connect(rotary, &RotaryHandler::rotated, this, &MainWindow::updateCount);
    connect(rotary, &RotaryHandler::switchChanged, this, &MainWindow::updateSwitch);

    workerThread.start();
}

MainWindow::~MainWindow()
{
    workerThread.quit();
    workerThread.wait();
    delete rotary;
    delete ui;
}

void MainWindow::updateCount(int newCount)
{
    counter += newCount;
    ui->labelCount->setText(QString::number(counter));
}

void MainWindow::updateSwitch(bool pressed)
{
    ui->labelSwitch->setText(pressed ? "Pressed" : "Released");
}

