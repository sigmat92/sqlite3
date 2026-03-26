#pragma once
#include <QObject>
#include <QString>
#include "model/patient.h"
/*
struct Patient {
    QString name;
    QString mobile;
    QString gender;
    int age = 0;
};
*/
class SessionService : public QObject
{
    Q_OBJECT
public:
    explicit SessionService(QObject* parent = nullptr);
    int createSession(int patientId);
    void reset();

    //const Patient& currentPatient() const;
    //QString currentPatientId() const;

public slots:
    void startSpo2();
    void startNibp();
    void startHeight();
    void startWeight();
    void startTemperature();

signals:
    void patientLoaded();
    void vitalsUpdated(int spo2, int pulse);

private:
    Patient m_patient;
    QString m_patientId;
};

