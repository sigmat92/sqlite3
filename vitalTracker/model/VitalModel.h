#pragma once
#include <QObject>

struct VitalData {
    double ecg;
    double resp;
    double spo2;
    int bpSys;
    int bpDia;
};

class VitalModel : public QObject {
    Q_OBJECT
public:
    explicit VitalModel(QObject* parent = nullptr);
    const VitalData& getData() const { return data; }
    void updateData();

signals:
    void dataUpdated(const VitalData& data);

private:
    VitalData data;
};

