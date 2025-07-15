#ifndef WAVEFORMWIDGET_H
#define WAVEFORMWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QVector>

enum class WaveType { Sine, Square, Triangle, Pulse };

class WaveformWidget : public QWidget {
    Q_OBJECT

public:
    WaveformWidget(QWidget *parent = nullptr);
    void start();
    void stop();
    void setWaveType(WaveType type);
    void setCustomWaveform(const QVector<double> &samples);
    QVector<double> getCurrentWaveform() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTimer *timer;
    WaveType currentWave;
    QVector<double> samples;
    int phase = 0;
    bool useCustom = false;

    void updateWave();
    void generateWave();
};
#endif // WAVEFORMWIDGET_H