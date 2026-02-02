#pragma once

#include <QObject>
#include <QString>

class PatientRepository : public QObject
{
    Q_OBJECT
public:
    explicit PatientRepository(QObject* parent = nullptr);

    // Save patient identity (once)
    bool savePatient(const QString& patientId,
                     const QString& name,
                     int age,
                     const QString& gender);

    // Save vitals (many times)
    bool saveVitals(const QString& patientId,
                    int spo2,
                    int pulse);
};

