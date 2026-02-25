#pragma once

#include <QString>

class PatientRepository
{
public:
    PatientRepository();
    
    int savePatient(const QString& name,
                    int age,
                    const QString& mobile,
                    const QString& gender);
    
    //bool savePatient(const QString& name,
    //                 int age,
    //                 const QString& mobile,
    //                 const QString& gender);

    bool saveVitals(int patientId,
                    int spo2,
                    int pulse);
};