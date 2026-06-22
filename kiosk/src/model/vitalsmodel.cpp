#include "vitalsmodel.h"
#include <QDebug>

VitalsModel::VitalsModel(QObject* parent)
    : QObject(parent)
{
}
void VitalsModel::setTemperature(double value, char unit)
{
    m_temperature = value;
    m_tempUnit = unit;

    qDebug() << "MODEL TEMP:" << value << unit;

    emit temperatureChanged(value, unit);
}
void VitalsModel::setSpO2(int spo2, int pulse)
{
    m_spo2 = spo2;
    m_pulse = pulse;

    emit spo2Changed(spo2, pulse);
}

void VitalsModel::setWeight(double weight)
{
    m_weight = weight;

    emit weightChanged(weight);
}

void VitalsModel::setHeight(int height)
{
    m_height = height;

    emit heightChanged(height);
}

void VitalsModel::setNIBP(int sys, int dia, int map)
{
    m_sys = sys;
    m_dia = dia;
    m_map = map;

    emit nibpChanged(sys, dia, map);
}
void VitalsModel::setNibpPressure(int pressure)
{
    qDebug() << "[MODEL] NIBP PRESSURE:" << pressure;

    emit nibpPressureChanged(pressure);
}
//void VitalsModel::setNibpPressure(int pressure)
//{
//    emit nibpPressureChanged(pressure);
//}
QString VitalsModel::farVision() const
{
    return m_farVision;
}

QString VitalsModel::nearVision() const
{
    return m_nearVision;
}
void VitalsModel::setNearVision(QString result)
{
    qDebug() << "[MODEL] Near Vision =" << result;
    m_nearVision = result;

    emit visionChanged(
            m_nearVision,
            m_farVision);

    emit visionFinal(
            m_nearVision,
            m_farVision);
}
void VitalsModel::setFarVision(QString result)
{
    qDebug() << "[MODEL] Far Vision =" << result;
    m_farVision = result;

    emit visionChanged(
            m_nearVision,
            m_farVision);

    emit visionFinal(
            m_nearVision,
            m_farVision);
}
/*
void VitalsModel::setVision(
        const QString& far,
        const QString& near)
{
    m_farVision = far;
    m_nearVision = near;

    emit visionChanged(far, near);

    emit visionFinal(far, near);
}
*/
int VitalsModel::height() const { return m_height; }
double VitalsModel::weight() const { return m_weight; }
double VitalsModel::temperature() const { return m_temperature; }
int VitalsModel::spo2() const { return m_spo2; }
int VitalsModel::pulse() const { return m_pulse; }
int VitalsModel::systolic() const { return m_sys; }
int VitalsModel::diastolic() const { return m_dia; }

// If not present, add members:
QString VitalsModel::patientId() const { return m_patientId; }
QString VitalsModel::timestamp() const { return m_timestamp; }