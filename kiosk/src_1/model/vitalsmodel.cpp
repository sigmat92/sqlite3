
#include "vitalsmodel.h"
#include <QtMath>
#include <QDebug>

VitalsModel::VitalsModel(QObject* parent)
    : QObject(parent)
{
}
void VitalsModel::setTemperature(double value, char unit)
{
    m_temperature = value;
    m_tempUnit = unit;

    qDebug() << "VitalsModel: temperatureChanged =" << value << unit;
    emit temperatureChanged(value, unit);
}
void VitalsModel::setSpO2(int spo2, int pulse)
{
    m_spo2 = spo2;
    m_pulse = pulse;

    qDebug() << "VitalsModel: SpO2Changed =" << spo2 << "%, Pulse =" << pulse << "bpm";
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

