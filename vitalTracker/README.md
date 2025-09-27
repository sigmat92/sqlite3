Project Architecture (MVC)

Model (VitalModel) → Holds the patient vital data (ECG, SpO2, Respiration, BP).

View (MainWindow + WaveformView) → The GUI (toolbar, waveform panels, labels).

Controller (VitalController) → Connects the model and the view, orchestrates updates.

This separation makes it clean and extensible.

1. main.cpp

#include "mainwindow.h"
#include "vitalmodel.h"
#include "vitalcontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    VitalModel model;              // create the data source
    MainWindow w;                  // create the GUI
    VitalController controller(&model, &w); // hook them together

    w.show();                      // show GUI
    return a.exec();               // start Qt event loop
}

This is the entry point:

Creates model, view, and controller.

Launches Qt’s GUI event loop.

2. VitalModel
vitalmodel.h

class VitalModel : public QObject {
    Q_OBJECT
public:
    explicit VitalModel(QObject *parent = nullptr);

    int heartRate() const;
    int spo2Value() const;
    int respRate() const;
    int bpSys() const;
    int bpDia() const;

    QVector<float> ecg() const;
    QVector<float> spo2() const;
    QVector<float> resp() const;
    QVector<float> bp() const;
};

vitalmodel.cpp

QVector<float> VitalModel::ecg() const {
    QVector<float> v(200);
    for(int i=0; i<200; i++) v[i] = sin(i*0.1f); // sine wave
    return v;
}

his simulates vital sign data:

heartRate() returns 72.

spo2Value() returns 98%.

ecg() generates a sine wave.

spo2(), resp(), bp() generate variations.

You can replace these later with real sensor input.

3. WaveformView
waveformview.h

class WaveformView : public QWidget {
    Q_OBJECT
public:
    explicit WaveformView(QWidget *parent = nullptr);
    void setSamples(const QVector<float> &samples);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<float> m_samples;
};


waveformview.cpp

void WaveformView::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if(m_samples.isEmpty()) return;

    QPolygonF poly;
    for(int i=0; i<m_samples.size(); i++) {
        float x = (float)i / m_samples.size() * width();
        float y = height()/2 - m_samples[i] * height()/2;
        poly << QPointF(x, y);
    }
    painter.setPen(Qt::green);
    painter.drawPolyline(poly);
}

This is a custom widget:

Stores a QVector<float> of samples.

Converts them into QPolygonF points.

Draws a polyline → your waveform.

Every time you call setSamples(), it stores data and repaints.

4. MainWindow

mainwindow.h

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateVitals(VitalModel *model);

private slots:
    void startPressed();

private:
    Ui::MainWindow *ui;
};

mainwindow.cpp

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->actionStart, &QAction::triggered, this, &MainWindow::startPressed);
}

void MainWindow::updateVitals(VitalModel *model) {
    ui->labelBp->setText(QString("BP: %1/%2 mmHg").arg(model->bpSys()).arg(model->bpDia()));
    ui->labelSpo2->setText(QString("SpO2: %1%").arg(model->spo2Value()));
    ui->labelResp->setText(QString("Resp: %1").arg(model->respRate()));
    ui->labelHr->setText(QString("HR: %1 bpm").arg(model->heartRate()));

    ui->ecgView->setSamples(model->ecg());
    ui->spo2View->setSamples(model->spo2());
    ui->respView->setSamples(model->resp());
    ui->bpView->setSamples(model->bp());
}

void MainWindow::startPressed() {
    // later: request controller to update periodically
}

Responsibilities:

Handles toolbar actions (e.g., actionStart).

Updates GUI labels and waveforms with model data.

VitalController

VitalController::VitalController(VitalModel *model, MainWindow *view, QObject *parent)
    : QObject(parent), m_model(model), m_view(view) {
    // Later: connect timers or signals
    m_view->updateVitals(m_model); // one-time update for now
}


Controller:

Mediates between model and view.

For now, just updates once.

Later: you add QTimer to refresh periodically (animate waveforms).

🔹 Execution Flow

Startup → main.cpp runs → creates model, view, controller.

View setup → MainWindow loads .ui (with promoted WaveformView widgets).

Controller calls updateVitals() → fills labels + plots waveforms.

WaveformView draws data with paintEvent().


