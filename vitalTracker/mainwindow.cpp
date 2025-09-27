#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect actions from toolbar
    connect(ui->actionStart, &QAction::triggered, this, &MainWindow::startPressed);
    connect(ui->actionMute, &QAction::triggered, this, &MainWindow::mutePressed);
    connect(ui->actionTimestamp, &QAction::triggered, this, &MainWindow::timestampPressed);

    // Example: animate sample data every 50ms
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        static float t = 0;
        QVector<float> sine, triangle;
        const int N = 200;

        for (int i = 0; i < N; i++) {
            float x = t + i * 0.1f;
            sine.append(sin(x));
            triangle.append(2.0f * (x/6.283185307f - floor(x/6.283185307f + 0.5f)));
        }
        t += 0.1f;

        ui->ecgView->setSamples(sine);
        ui->spo2View->setSamples(triangle);
        ui->respView->setSamples(sine);
        ui->bpView->setSamples(triangle);

        ui->labelEcg->setText(QString("HR: %1 bpm").arg(int(60 + 10 * sin(t))));
        ui->labelSpo2->setText(QString("SpO₂: %1%").arg(int(95 + 3 * sin(t))));
        ui->labelResp->setText(QString("Resp: %1 bpm").arg(int(16 + 2 * sin(t))));
        ui->labelBp->setText(QString("BP: %1/%2 mmHg").arg(120 + int(5*sin(t))).arg(80 + int(3*sin(t))));
    });
    timer->start(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateVitals(VitalModel *model)
{
    ui->labelEcg->setText(QString("HR: %1 bpm").arg(model->heartRate()));
    ui->labelSpo2->setText(QString("SpO₂: %1%").arg(model->spo2Value()));
    ui->labelResp->setText(QString("Resp: %1 bpm").arg(model->respRate()));
    ui->labelBp->setText(QString("BP: %1/%2 mmHg").arg(model->bpSys()).arg(model->bpDia()));

    ui->ecgView->setSamples(model->ecg());
    ui->spo2View->setSamples(model->spo2());
    ui->respView->setSamples(model->resp());
    ui->bpView->setSamples(model->bp());
}

// Example slot implementations
void MainWindow::startPressed() { qDebug("Start pressed"); }
void MainWindow::mutePressed() { qDebug("Mute pressed"); }
void MainWindow::timestampPressed() { qDebug("Timestamp pressed"); }

