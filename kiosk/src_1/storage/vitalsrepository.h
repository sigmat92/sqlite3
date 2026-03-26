#pragma once

#include <sqlite3.h>

class VitalsRepository
{
public:
    VitalsRepository() = default;

    bool saveSpO2(int sessionId, int spo2, int pulse);
    bool saveTemperature(int sessionId, double temperature);
    bool saveWeight(int sessionId, double weight);
    bool saveHeight(int sessionId, int height);
    bool saveNIBP(int sessionId, int systolic, int diastolic);
};
