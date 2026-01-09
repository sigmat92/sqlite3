#include "WaveformWidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>
#include <cmath>

WaveformWidget::WaveformWidget(WaveformType t, QWidget *parent)
    : QWidget(parent), 
      type(t),
      //maxPoints(0),
      maxPoints(10),
      phase(0.0),
      phaseStep(2.5)   // tweak this for animation speed
{
    //maxPoints = 0;
    setMinimumHeight(100);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::black);
    setPalette(pal);
        // animation timer (approx 30 FPS)
    animTimer = new QTimer(this);
    connect(animTimer, &QTimer::timeout, this, [this]() {
        phase += phaseStep;
        // keep phase bounded to avoid overflow
        if (phase > 1e6) phase = 0.0;
        // only repaint if we're drawing procedural waves (or we want continuous motion)
        update();
    });
    animTimer->start(33);
}

void WaveformWidget::clearValues() {
    values.clear();
    update();
}

void WaveformWidget::resizeEvent(QResizeEvent *event) {
    maxPoints = width();
    if (values.size() > maxPoints)
        values = values.mid(values.size()-maxPoints);
    QWidget::resizeEvent(event);
}

void WaveformWidget::addValue(double val) {
    if (maxPoints == 0) maxPoints = width();
    values.append(val);
    if (values.size() > maxPoints) values.remove(0, values.size() - maxPoints);
    update();
}
/*
void WaveformWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor color;
    switch (type) {
        case ECG:   color = Qt::green; break;
        case RESP:  color = Qt::cyan; break;
        case SPO2:  color = Qt::gray; break;
        case BP:    color = Qt::yellow; break;
    }
    painter.setPen(QPen(color, 2));

    QPainterPath path;
    int w = width();
    int h = height();
    int mid = h / 2;

    // Draw waveform by type
    if (type == ECG || type == SPO2) {
        // ---------- sine wave ----------
        for (int x = 0; x < w; ++x) {
            double y = mid - (mid * 0.6) * sin((x + phase) * 0.05);
            if (x == 0) path.moveTo(x, y);
            else path.lineTo(x, y);
        }
    } else if (type == RESP) {
        // ---------- triangular wave ----------
        for (int x = 0; x < w; ++x) {
            double period = 100.0;
            double pos = fmod(x + phase, period) / period;
            double y;
            if (pos < 0.5) {
                y = mid - (mid * 0.6) * (pos * 2);          // rising
            } else {
                y = mid - (mid * 0.6) * (2 - pos * 2);      // falling
            }
            if (x == 0) path.moveTo(x, y);
            else path.lineTo(x, y);
        }
    } else if (type == BP) {
        // ---------- square-like pulse ----------
        for (int x = 0; x < w; ++x) {
            double period = 80.0;
            double pos = fmod(x + phase, period) / period;
            double y = (pos < 0.2) ? mid - (mid * 0.7) : mid + (mid * 0.5);
            if (x == 0) path.moveTo(x, y);
            else path.lineTo(x, y);
        }
    }

    painter.drawPath(path);

    // shift phase for animation
    phase += 2;
    if (phase > w) phase = 0;
}
*/


void WaveformWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    if (values.isEmpty()) return;

    QColor color;
    switch(type){
        case ECG:  color = Qt::green; break;
        case RESP: color = Qt::cyan; break;
        case SPO2: color = Qt::gray; break;
        case BP:   color = Qt::yellow; break;
    }

    painter.setPen(QPen(color,2));

    QPainterPath path;
    path.moveTo(0, height()/2 - values[0]*height()/2);

    int step = width() / (values.size() > 1 ? values.size()-1 : 1);
    for (int i=1; i<values.size(); ++i){
        double y = height()/2 - values[i]*height()/2;
        path.lineTo(i*step, y);
    }
    painter.drawPath(path);
}

