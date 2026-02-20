#include "patientrepository.h"
//#include "../storage/sqliterecorder.h"
#include <QDebug>
//PatientRepository::PatientRepository(SQLiteRecorder* db)
//    : m_db(db)
//{
//}
PatientRepository::PatientRepository(QObject* parent)
    : QObject(parent)
{
}

bool PatientRepository::savePatient(const QString& patientId,
                                    const QString& name,
                                    int age,
                                    const QString& gender)
{
    qDebug() << "Saving patient:"
             << patientId << name << age << gender;
    return true;
}

bool PatientRepository::saveVitals(const QString& patientId,
                                   int spo2,
                                   int pulse)
{
    qDebug() << "Saving vitals:"
             << patientId << spo2 << pulse;
    return true;
}

