#pragma once
#include <QWidget>
#include <QVector>

#include <QVector>
#include <QTimer>


class WaveformWidget : public QWidget {
    Q_OBJECT
public:
    enum WaveformType { ECG, RESP, SPO2, BP };

    explicit WaveformWidget(WaveformType t, QWidget *parent = nullptr);
    void addValue(double val);
    void clearValues();
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    WaveformType type;
    QVector<double> values;
    int maxPoints;
    // animation for procedural waves
    double phase;          // advances over time to animate generated waves
    double phaseStep;      // increment per animation tick
    QTimer* animTimer;     // drives animation
};

