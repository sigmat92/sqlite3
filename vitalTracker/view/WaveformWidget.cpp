#include "WaveformWidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>

WaveformWidget::WaveformWidget(WaveformType t, QWidget *parent)
    : QWidget(parent), type(t)
{
    maxPoints = 0;
    setMinimumHeight(100);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::black);
    setPalette(pal);
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

void WaveformWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    if (values.isEmpty()) return;

    QColor color;
    switch(type){
        case ECG:  color = Qt::cyan; break;
        case RESP: color = Qt::green; break;
        case SPO2: color = Qt::yellow; break;
        case BP:   color = Qt::lightGray; break;
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

