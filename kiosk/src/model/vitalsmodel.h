#pragma once
#include <QObject>

class VitalsModel : public QObject
{
    Q_OBJECT
public:
    explicit VitalsModel(QObject* parent = nullptr);

public slots:
    void setTemperature(double value, char unit);

signals:
    void temperatureChanged(double value, char unit);

private:
    double m_temperature{0.0};
    char   m_tempUnit{'F'}; 
};

