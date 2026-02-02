#include "sessionservice.h"

SessionService::SessionService(QObject* parent)
    : QObject(parent)
{
}

void SessionService::reset()
{
    m_patient = Patient{};
    m_patientId.clear();
}

const Patient& SessionService::currentPatient() const
{
    return m_patient;
}

QString SessionService::currentPatientId() const
{
    return m_patientId;
}

