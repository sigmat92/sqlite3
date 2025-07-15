#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waveformwidget.h"
#include "waveformdb.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->comboWaveType->addItems({"Sine", "Square", "Triangle", "Pulse"});
    connectSignals();
    refreshSavedList();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::connectSignals() {
    connect(ui->btnStart, &QPushButton::clicked, this, [&]() {
        ui->waveWidget->start();
    });
    connect(ui->btnStop, &QPushButton::clicked, this, [&]() {
        ui->waveWidget->stop();
    });
    connect(ui->comboWaveType, &QComboBox::currentIndexChanged, this, [&](int index) {
        ui->waveWidget->setWaveType(static_cast<WaveType>(index));
    });
    connect(ui->btnSave, &QPushButton::clicked, this, [&]() {
        QString name = ui->editName->text();
        if (!name.isEmpty()) {
            WaveformDB::instance().save(name, ui->waveWidget->getCurrentWaveform());
            refreshSavedList();
        }
    });
    connect(ui->btnLoad, &QPushButton::clicked, this, [&]() {
        QString name = ui->comboSaved->currentText();
        auto data = WaveformDB::instance().load(name);
        if (!data.isEmpty()) {
            ui->waveWidget->setCustomWaveform(data);
        }
    });
}

void MainWindow::refreshSavedList() {
    ui->comboSaved->clear();
    ui->comboSaved->addItems(WaveformDB::instance().listWaveforms());
}