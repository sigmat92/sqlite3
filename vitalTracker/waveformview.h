#ifndef WAVEFORMVIEW_H
#define WAVEFORMVIEW_H

#include <QWidget>
#include <QVector>

class WaveformView : public QWidget
{
    Q_OBJECT
public:
    explicit WaveformView(QWidget *parent = nullptr);

    // Accept float samples directly
    void setSamples(const QVector<float> &samples);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<float> m_samples;
};

#endif // WAVEFORMVIEW_H

