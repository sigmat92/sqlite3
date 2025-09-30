#include "MainWindow.h"
#include <QFont>
#include <QPalette>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // ------------------ Header ------------------
    QHBoxLayout *headerLayout = new QHBoxLayout();
    bedLabel  = new QLabel("Bed: 01");
    bedLabel->setFont(QFont("Arial", 18, QFont::Bold));
    bedLabel->setStyleSheet("QLabel { color: white; }");

    timeLabel = new QLabel();
    timeLabel->setFont(QFont("Arial", 18, QFont::Bold));
    timeLabel->setStyleSheet("QLabel { color: white; }");

    headerLayout->addWidget(bedLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(timeLabel);
    mainLayout->addLayout(headerLayout);

    // ------------------ ECG ------------------
    ecgWidget = new WaveformWidget(WaveformWidget::ECG, this);
    ecgLabel  = new QLabel("0.00");
    ecgLabel->setFont(QFont("Arial", 20, QFont::Bold));
    ecgLabel->setStyleSheet("QLabel { color: cyan; border: 2px solid cyan; padding: 5px; }");

    QHBoxLayout *ecgLayout = new QHBoxLayout();
    ecgLayout->addWidget(ecgWidget);
    ecgLayout->addWidget(ecgLabel);
    mainLayout->addLayout(ecgLayout);

    // ------------------ RESP ------------------
    respWidget = new WaveformWidget(WaveformWidget::RESP, this);
    respLabel  = new QLabel("0.00");
    respLabel->setFont(QFont("Arial", 20, QFont::Bold));
    respLabel->setStyleSheet("QLabel { color: green; border: 2px solid green; padding: 5px; }");

    QHBoxLayout *respLayout = new QHBoxLayout();
    respLayout->addWidget(respWidget);
    respLayout->addWidget(respLabel);
    mainLayout->addLayout(respLayout);

    // ------------------ SPO2 ------------------
    spo2Widget = new WaveformWidget(WaveformWidget::SPO2, this);
    spo2Label  = new QLabel("0%");
    spo2Label->setFont(QFont("Arial", 20, QFont::Bold));
    spo2Label->setStyleSheet("QLabel { color: yellow; border: 2px solid yellow; padding: 5px; }");

    QHBoxLayout *spo2Layout = new QHBoxLayout();
    spo2Layout->addWidget(spo2Widget);
    spo2Layout->addWidget(spo2Label);
    mainLayout->addLayout(spo2Layout);

    // ------------------ BP ------------------
    bpWidget = new WaveformWidget(WaveformWidget::BP, this);
    bpLabel  = new QLabel("0/0");
    bpLabel->setFont(QFont("Arial", 20, QFont::Bold));
    bpLabel->setStyleSheet("QLabel { color: lightgray; border: 2px solid lightgray; padding: 5px; }");

    QHBoxLayout *bpLayout = new QHBoxLayout();
    bpLayout->addWidget(bpWidget);
    bpLayout->addWidget(bpLabel);
    mainLayout->addLayout(bpLayout);

    // ------------------ Footer ------------------
    footerLabel = new QLabel("Status: Monitoring");
    footerLabel->setFont(QFont("Arial", 16));
    footerLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(footerLabel);

    setLayout(mainLayout);
    setStyleSheet("background-color: black; color: white;");

    // ------------------ Timer for clock ------------------
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    timer->start(1000);  // update every second
    updateTime(); // initial time
}

// ------------------ Public setters ------------------
void MainWindow::setECG(double val)  { ecgLabel->setText(QString::number(val, 'f', 2)); }
void MainWindow::setRESP(double val) { respLabel->setText(QString::number(val, 'f', 2)); }
void MainWindow::setSPO2(double val) { spo2Label->setText(QString::number(val, 'f', 0) + "%"); }
void MainWindow::setBP(int sys, int dia) { bpLabel->setText(QString("%1/%2").arg(sys).arg(dia)); }
void MainWindow::setFooterText(const QString &text) { footerLabel->setText(text); }

// ------------------ Update Time ------------------
void MainWindow::updateTime() {
    QString currentTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    timeLabel->setText(currentTime);
}

