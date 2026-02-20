#include "vitalsservice.h"

VitalsService::VitalsService(QObject* parent)
    : QObject(parent)
{
    m_expected = {
        "temperature",
        "spo2",
        "weight",
        "height",
        "nibp"
    };
}

void VitalsService::startMeasurement()
{
    m_completed.clear();

    for (const QString& s : m_expected) {
        emit sensorBusy(s, true);
        startTimeout(s);
    }
}

void VitalsService::startTimeout(const QString& name)
{
    QTimer* t = new QTimer(this);
    t->setSingleShot(true);

    connect(t, &QTimer::timeout, this, [this, name]() {
        if (!m_completed.contains(name)) {
            emit sensorMissing(name);
            emit sensorBusy(name, false);
            m_completed.insert(name);
            checkCompletion();
        }
    });

    t->start(5000);
    m_timers[name] = t;
}

void VitalsService::markComplete(const QString& name)
{
    if (m_completed.contains(name))
        return;

    m_completed.insert(name);

    if (m_timers.contains(name))
        m_timers[name]->stop();

    emit sensorBusy(name, false);
    checkCompletion();
}

void VitalsService::checkCompletion()
{
    if (m_completed.size() == m_expected.size())
        emit measurementFinished();
}
//temperature
void VitalsService::onTemperatureRaw(double value, char unit)
{
    if (value <= 0)
        return;

    emit temperatureReady(value, unit);
    markComplete("temperature");
}
//SpO2
void VitalsService::onSpO2Raw(int spo2, int pulse)
{
    if (spo2 <= 0)
        return;

    emit spo2Ready(spo2, pulse);
    markComplete("spo2");
}
//Weight
void VitalsService::onWeightRaw(double weight)
{
    if (weight <= 0)
        return;

    emit weightReady(weight);
    markComplete("weight");
}
//Height
void VitalsService::onHeightRaw(int height)
{
    if (height <= 0)
        return;

    emit heightReady(height);
    markComplete("height");
}
//NIBP
void VitalsService::onNibpRaw(int sys, int dia, int map)
{
    if (sys <= 0 || dia <= 0)
        return;

    emit nibpReady(sys, dia, map);
    markComplete("nibp");
}