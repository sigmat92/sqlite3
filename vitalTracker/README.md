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

1. Header: WaveformWidget.h
class WaveformWidget : public QWidget {
    Q_OBJECT

public:
    enum WaveformType { ECG, RESP, SPO2, BP };

    explicit WaveformWidget(WaveformType type, QWidget *parent = nullptr);
    void addValue(double val);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    WaveformType type;
    QVector<double> values;
    int maxPoints;
};

Explanation

WaveformType — an enum to identify which waveform this widget will draw (ECG, RESP, etc.).

values — a dynamic array of doubles storing waveform points.

maxPoints — limits how many points we store. This prevents old points from accumulating, which was causing the waveforms to slow down.

paintEvent — called automatically by Qt when the widget needs to redraw.

resizeEvent — called when the widget size changes. This lets us adjust maxPoints dynamically so the waveform always fills the width.

2. Constructor: WaveformWidget.cpp
WaveformWidget::WaveformWidget(WaveformType t, QWidget *parent)
    : QWidget(parent), type(t), maxPoints(0)
{
    setMinimumHeight(100);
    setMaximumHeight(150);
    setStyleSheet("background-color: black;");
}

Explanation

Initializes the widget with a black background.

maxPoints is initially 0 — will be set when we know the widget width.

setMinimumHeight / setMaximumHeight ensures the widget is tall enough for readability.

3. Adding Values: addValue(double val)
void WaveformWidget::addValue(double val) {
    if (maxPoints == 0) maxPoints = width();  // set max points according to width
    if (values.size() >= maxPoints) values.pop_front(); // remove oldest value
    values.append(val);
    update(); // trigger repaint
}

Explanation

Each time new data arrives (e.g., ECG sample), call addValue().

Circular buffer logic:

Only keep maxPoints elements.

pop_front() removes the oldest point when the buffer is full.

update() triggers Qt's paintEvent — redraws the waveform.

Why this fixes accumulation:
Before, all points were kept forever → memory & repaint slowed down. Now only the last width() points are stored, keeping performance smooth.

4. Handling Resize: resizeEvent
void WaveformWidget::resizeEvent(QResizeEvent *event) {
    maxPoints = width();
    while (values.size() > maxPoints) values.pop_front();
    QWidget::resizeEvent(event);
}

Explanation

When the widget width changes:

Adjust maxPoints to the new width.

Remove extra points to fit the new width.

Ensures the waveform always fills the widget and doesn’t overflow.

5. Drawing the waveform: paintEvent
void WaveformWidget::paintEvent(QPaintEvent *) {
    if (values.isEmpty()) return;

    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    QColor color;
    switch (type) {
        case ECG:  color = Qt::cyan; break;
        case RESP: color = Qt::green; break;
        case SPO2: color = Qt::yellow; break;
        case BP:   color = Qt::lightGray; break;
    }

    QPen pen(color, 2);
    painter.setPen(pen);

    QPainterPath path;
    int h = height();
    int count = values.size();

    for (int i = 0; i < count; ++i) {
        double val = values[i];
        int y = h - int(val * h); // vertical scaling (0-1)
        if (i == 0)
            path.moveTo(i, y);
        else
            path.lineTo(i, y);
    }

    painter.drawPath(path);
}

Step by step

if (values.isEmpty()) return; — nothing to draw yet.

QPainter painter(this); — paint on this widget.

fillRect(rect(), Qt::black); — black background.

QColor color; switch(type) — select color based on waveform type.

QPen pen(color, 2) — set pen color and thickness.

QPainterPath path; — path for the waveform line.

Loop through all points:

Convert the value (0–1 normalized) to pixel Y.

moveTo first point, then lineTo for each subsequent point.

painter.drawPath(path); — finally render the waveform.

Why this is fast:

Only draws the current set of points, not everything ever.

Using QPainterPath instead of drawing each line individually reduces Qt overhead.

6. How to Use in MainWindow
ecgWidget = new WaveformWidget(WaveformWidget::ECG);
spo2Widget = new WaveformWidget(WaveformWidget::SPO2);

ecgWidget->addValue(newECGValue);
spo2Widget->addValue(newSPO2Value);


Each widget independently maintains its buffer.

UI remains responsive.

Vitals can be shown in colored boxes next to the waveform (same color as the line).

 Key Benefits of This Implementation

Smooth real-time waveform → no lag or accumulation.

Dynamic resizing → waveform always fills widget.

Colored waveforms → matches vitals labels.

Efficient memory usage → only keep the last width() points.

Easy to add new waveforms → just instantiate a new WaveformWidget.
