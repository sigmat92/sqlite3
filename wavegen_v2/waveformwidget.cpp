#include "waveformwidget.h"
#include <QPainter>
#include <cmath>

WaveformWidget::WaveformWidget(QWidget *parent)
    : QWidget(parent), timer(new QTimer(this)), currentWave(WaveType::Sine) {
    connect(timer, &QTimer::timeout, this, &WaveformWidget::updateWave);
}

void WaveformWidget::start() {
    useCustom = false;
    generateWave();
    timer->start(50);
}

void WaveformWidget::stop() {
    timer->stop();
}

void WaveformWidget::setWaveType(WaveType type) {
    currentWave = type;
    useCustom = false;
    generateWave();
    update();
}

void WaveformWidget::setCustomWaveform(const QVector<double> &data) {
    samples = data;
    useCustom = true;
    update();
}

QVector<double> WaveformWidget::getCurrentWaveform() const {
    return samples;
}

void WaveformWidget::updateWave() {
    phase = (phase + 1) % samples.size();
    update();
}

void WaveformWidget::generateWave() {
    samples.clear();
    for (int i = 0; i < 100; ++i) {
        double val = 0;
        switch (currentWave) {
            case WaveType::Sine: val = sin(i * 2 * M_PI / 100); break;
            case WaveType::Square: val = (i < 50) ? 1.0 : -1.0; break;
            case WaveType::Triangle: val = 2 * fabs(2 * (i / 100.0 - floor(i / 100.0 + 0.5))) - 1; break;
            case WaveType::Pulse: val = (i % 20 < 5) ? 1.0 : 0.0; break;
        }
        samples.append(val);
    }
}

void WaveformWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.fillRect(rect(), Qt::black);
    p.setPen(Qt::green);

    int w = width(), h = height();
    for (int i = 1; i < samples.size(); ++i) {
        int x1 = (i - 1) * w / samples.size();
        int y1 = h / 2 - samples[(i - 1 + phase) % samples.size()] * (h / 2 - 10);
        int x2 = i * w / samples.size();
        int y2 = h / 2 - samples[(i + phase) % samples.size()] * (h / 2 - 10);
        p.drawLine(x1, y1, x2, y2);
    }
}