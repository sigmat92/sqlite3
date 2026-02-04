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

/*
void VitalsModel::setTemperature(double t)
{
    if (qFuzzyCompare(m_temperature, t))
        return;

    m_temperature = t;
    qDebug() << "VitalsModel instance:" << this;

    qDebug() << "VitalsModel: temperatureChanged =" << t;
    emit temperatureChanged(t);
}
*/
