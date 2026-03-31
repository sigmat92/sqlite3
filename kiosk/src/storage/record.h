#pragma once

#include <QString>

struct Record
{
    int sessionId;
    int patientId;
    QString date;
    QString time;
    QString name;
};