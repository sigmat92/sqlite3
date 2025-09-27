#include "vitalmodel.h"

VitalModel::VitalModel(QObject *parent) : QObject(parent) {}

int VitalModel::heartRate() const { return 72; }
int VitalModel::spo2Value() const { return 98; }
int VitalModel::respRate() const { return 16; }
int VitalModel::bpSys() const { return 120; }
int VitalModel::bpDia() const { return 80; }

QVector<float> VitalModel::ecg() const {
    QVector<float> v(200);
    for(int i=0;i<200;i++) v[i] = sin(i*0.1f);
    return v;
}

QVector<float> VitalModel::spo2() const {
    QVector<float> v(200);
    for(int i=0;i<200;i++) v[i] = 0.5f * sin(i*0.05f) + 0.5f;
    return v;
}

QVector<float> VitalModel::resp() const { return ecg(); }
QVector<float> VitalModel::bp() const { return spo2(); }

