

#pragma once
#include <QObject>

class VitalsModel : public QObject
{
    Q_OBJECT
public:
    explicit VitalsModel(QObject* parent = nullptr);
    
    int height() const;
    double weight() const;
    double temperature() const;
    int spo2() const;
    int pulse() const;
    int systolic() const;
    int diastolic() const;
    
    QString patientId() const;
    QString timestamp() const;

public slots:
    void setTemperature(double value, char unit);
    void setSpO2(int spo2, int pulse);
    void setWeight(double weight);
    void setHeight(int height);
    void setNIBP(int sys, int dia, int map);
    void setNibpPressure(int pressure);
    
signals:
    void temperatureChanged(double value, char unit);
    void spo2Changed(int spo2, int pulse);
    void weightChanged(double weight);
    void heightChanged(int height);
    void nibpChanged(int sys, int dia, int map);
    
    void nibpPressureChanged(int pressure);
    
    //void setNibpPressure(int pressure);

    // FINAL STABLE SIGNALS
    void temperatureFinal(double value);
    void spo2Final(int spo2, int pulse);
    void weightFinal(double weight);
    void heightFinal(int height);
    void nibpFinal(int sys, int dia);

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

    private:
    QString m_patientId;
    QString m_timestamp;

    //int m_systolic{0};
    //int m_diastolic{0};
};

