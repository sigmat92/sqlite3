

#pragma once
#include <QObject>

class VitalsModel : public QObject
{
    Q_OBJECT
public:
    explicit VitalsModel(QObject* parent = nullptr);

public slots:
    void setTemperature(double value, char unit);
    void setSpO2(int spo2, int pulse);
    void setWeight(double weight);
    void setHeight(int height);
    void setNIBP(int sys, int dia, int map);

signals:
    void temperatureChanged(double value, char unit);
    void spo2Changed(int spo2, int pulse);
    void weightChanged(double weight);
    void heightChanged(int height);
    void nibpChanged(int sys, int dia, int map);

private:
    double m_temperature{0.0};
    char   m_tempUnit{'F'}; 
    int    m_spo2{0};
    int    m_pulse{0};

    double m_weight{0.0};
    int m_height{0};
    int m_sys{0};
    int m_dia{0};
    int m_map{0};
};

