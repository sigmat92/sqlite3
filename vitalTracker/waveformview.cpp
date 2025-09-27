#include "waveformview.h"
#include <QPainter>

WaveformView::WaveformView(QWidget *parent)
    : QWidget(parent)
{
    setMinimumHeight(120);
    setMinimumWidth(200);
}

void WaveformView::setSamples(const QVector<float> &samples)
{
    m_samples = samples;
    update(); // trigger repaint
}

void WaveformView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.fillRect(rect(), Qt::black);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(QPen(Qt::green, 2));

    if (m_samples.isEmpty())
        return;

    double dx = (double)width() / (m_samples.size() - 1);
    QPointF prev(0, height() / 2 - m_samples[0] * (height() / 2));

    for (int i = 1; i < m_samples.size(); i++)
    {
        double y = height() / 2 - m_samples[i] * (height() / 2);
        QPointF pt(i * dx, y);
        p.drawLine(prev, pt);
        prev = pt;
    }
}

