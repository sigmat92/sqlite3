#include "vitalsservice.h"
#include <QDebug>

VitalsService::VitalsService(QObject* parent)
    : QObject(parent)
{
    timeout.setSingleShot(true);

    connect(&timeout,&QTimer::timeout,this,[this](){
        qDebug()<<"Timeout!";
        setIdle();
    });
}

// ---------- REQUESTS ----------

void VitalsService::requestTemperature()
{
    if(state!=State::Idle) return;
    state=State::Temp;

    emit sendCommand(QByteArray("\x96\xAA\x54",3));
    startTimeout();
}

void VitalsService::requestSpo2()
{
    if(state!=State::Idle) return;
    state=State::Spo2;

    emit sendCommand(QByteArray("\x96\xAA\x53",3));
    startTimeout();
}

void VitalsService::requestNibp()
{
    if(state!=State::Idle) return;
    state=State::Nibp;

    emit sendCommand(QByteArray("\x96\xAA\x4E",3));
    startTimeout();
}

void VitalsService::requestWeight()
{
    if(state!=State::Idle) return;
    state=State::Weight;

    emit sendCommand(QByteArray("\x96\xAA\x57",3));
    startTimeout();
}

void VitalsService::requestHeight()
{
    if(state!=State::Idle) return;
    state=State::Height;

    emit sendCommand(QByteArray("\x96\xAA\x48",3));
    startTimeout();
}

// ---------- RESPONSES ----------

void VitalsService::onTemperature(double v, char unit)
{
    if(state!=State::Temp) return;
    if(v<=1.0) return;

    emit temperatureReady(v, unit); 
    setIdle();
}

void VitalsService::onSpo2(int s,int p)
{
    if(state!=State::Spo2) return;
    emit spo2Ready(s,p);
    setIdle();
}

void VitalsService::onNibp(int sys,int dia,int pulse)
{
    if(state!=State::Nibp) return;
    emit nibpReady(sys,dia,pulse);
    setIdle();
}

void VitalsService::onWeight(double w)
{
    if(state!=State::Weight) return;
    emit weightReady(w);
    setIdle();
}

void VitalsService::onHeight(double h)
{
    if(state!=State::Height) return;
    emit heightReady(h);
    setIdle();
}

// ---------- INTERNAL ----------

void VitalsService::setIdle()
{
    state=State::Idle;
    timeout.stop();
}

void VitalsService::startTimeout()
{
    timeout.start(20000);
}
