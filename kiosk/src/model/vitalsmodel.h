#pragma once
#include <QObject>

class VitalsModel : public QObject
{
    Q_OBJECT
public:
    explicit VitalsModel(QObject *parent = nullptr);
    int spo2() const {return m_spo2;}
    float temperature() const {return m_temp;}
signals:
    void temperatureChanged(float t);
    void updated();

public slots:
    void setSpo2(int v);
    void setPulseRate(int bpm);
    void setTemperature(float t);

private:
    int m_spo2 = 0;
    int m_pulse = 0;
    float m_temp = 0.0f;
};

