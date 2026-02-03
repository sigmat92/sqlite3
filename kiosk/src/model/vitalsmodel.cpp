#include "vitalsmodel.h"


VitalsModel::VitalsModel(QObject *parent)
    : QObject(parent)
{
}

void VitalsModel::setSpo2(int v) {
    m_spo2 = v;
    emit updated();
}

void VitalsModel::setTemperature(float t) {
    if (qFuzzyCompare(m_temp, t))
        return;
    m_temp = t;
    //emit updated();
    emit temperatureChanged(t);
}

void VitalsModel::setPulseRate(int bpm) {
    m_pulse = bpm;
    emit updated();
}


