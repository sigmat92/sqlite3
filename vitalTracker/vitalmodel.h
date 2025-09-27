#ifndef VITALMODEL_H
#define VITALMODEL_H

#include <QObject>
#include <QVector>
#include <QtMath>

class VitalModel : public QObject
{
    Q_OBJECT
public:
    explicit VitalModel(QObject *parent = nullptr);

    int heartRate() const;
    int spo2Value() const;
    int respRate() const;
    int bpSys() const;
    int bpDia() const;

    QVector<float> ecg() const;
    QVector<float> spo2() const;
    QVector<float> resp() const;
    QVector<float> bp() const;
};

#endif // VITALMODEL_H

