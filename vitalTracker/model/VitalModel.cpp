#include "VitalModel.h"
#include <random>

VitalModel::VitalModel(QObject* parent) : QObject(parent)
{
    data = {0, 0, 0, 120, 80};
}

void VitalModel::updateData()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<> ecgDist(0.0, 1.0);
    std::uniform_real_distribution<> respDist(0.0, 1.0);
    std::uniform_int_distribution<> spo2Dist(95, 100);
    std::uniform_int_distribution<> bpSysDist(110, 140);
    std::uniform_int_distribution<> bpDiaDist(70, 90);

    data.ecg  = ecgDist(gen);
    data.resp = respDist(gen);
    data.spo2 = spo2Dist(gen);
    data.bpSys = bpSysDist(gen);
    data.bpDia = bpDiaDist(gen);

    emit dataUpdated(data);
}

