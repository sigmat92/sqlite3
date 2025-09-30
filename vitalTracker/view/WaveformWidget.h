#pragma once
#include <QWidget>
#include <QVector>

class WaveformWidget : public QWidget {
    Q_OBJECT
public:
    enum WaveformType { ECG, RESP, SPO2, BP };

    explicit WaveformWidget(WaveformType t, QWidget *parent = nullptr);
    void addValue(double val);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    WaveformType type;
    QVector<double> values;
    int maxPoints;
};

