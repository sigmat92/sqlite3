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
    m_temp = t;
    emit updated();
}

void VitalsModel::setPulseRate(int bpm) {
    m_pulse = bpm;
    emit updated();
}

