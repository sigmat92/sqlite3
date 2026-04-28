#pragma once

#include <QVariantMap>

class VitalsRepository
{
public:
    bool saveTemperature(int sessionId, double temperature);
    bool saveSpO2(int sessionId, int spo2, int pulse);
    bool saveWeight(int sessionId, double weight);
    bool saveHeight(int sessionId, int height);
    bool saveNIBP(int sessionId, int systolic, int diastolic);
    bool saveSession(int sessionId);

    QVariantMap getLatestVitals(int sessionId);
    bool createEmptyVitals(int sessionId);
};