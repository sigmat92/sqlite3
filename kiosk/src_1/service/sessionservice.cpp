
#include "sessionservice.h"
#include <QDebug>

SessionService::SessionService(QObject* parent)
    : QObject(parent)
{
}

void SessionService::startSpo2()
{
    qDebug() << "SessionService: Starting SpO2 measurement";
    // TODO: trigger SpO2 device
}

void SessionService::startNibp()
{
    qDebug() << "SessionService: Starting NIBP measurement";
}

void SessionService::startHeight()
{
    qDebug() << "SessionService: Starting Height measurement";
}

void SessionService::startWeight()
{
    qDebug() << "SessionService: Starting Weight measurement";
}

void SessionService::startTemperature()
{
    qDebug() << "SessionService: Starting Temperature measurement";
}
