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

// ---------------- SESSION ----------------

void VitalsService::setSessionId(int id)
{
    qDebug() << "Session setting in vitals service :" << id;
    m_sessionId = id;
}

// ---------------- REQUESTS ----------------

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
    qDebug() << "Sending Spo2 request for session :" << m_sessionId;
    emit sendCommand(QByteArray("\x96\xAA\xF4",3));
    startTimeout();
}

void VitalsService::requestNibp()
{
    if(state!=State::Idle) return;
    state=State::Nibp;
    qDebug() << "Sending NIBP request for session :" << m_sessionId;
    emit sendCommand(QByteArray("\x96\xAA\xF5\x01\x01",5));
    startTimeout();
}

void VitalsService::requestWeight()
{
    if(state!=State::Idle) return;
    state=State::Weight;
    qDebug() << "Sending Weight request for session :" << m_sessionId;
    emit sendCommand(QByteArray("\x96\xAA\xF8",3));
    startTimeout();
}

void VitalsService::requestHeight()
{
    if(state!=State::Idle) return;
    state=State::Height;
    qDebug() << "Sending Height request for session :" << m_sessionId;
    emit sendCommand(QByteArray("\x96\xAA\xF7",3));
    startTimeout();
}

// ---------------- RESPONSES ----------------

void VitalsService::onTemperature(double v, char unit)
{
    if(state!=State::Temp) return;
    if(v<=1.0) return;

    if(m_repo && m_sessionId > 0)
    {
        qDebug()<<" Saving TEMP from VitalsService calling repo method:"<<v;
        m_repo->saveTemperature(m_sessionId,v);
    }
    qDebug() << "copying into current_vitals";
    //currentVitals.setTemperature(v);
    qDebug() << "SessionId in DB in VitalsService:" << m_sessionId;
    emit temperatureReady(v,unit);
    setIdle();
}

void VitalsService::onSpo2(int s,int p)
{
    if(state!=State::Spo2) return;

    if(m_repo && m_sessionId > 0)
        m_repo->saveSpO2(m_sessionId,s,p);

    emit spo2Ready(s,p);
    setIdle();
}

void VitalsService::onNibp(int sys,int dia,int map)
{
    if(state!=State::Nibp) return;

    if(m_repo && m_sessionId > 0)
        m_repo->saveNIBP(m_sessionId,sys,dia);

    emit nibpReady(sys,dia,map);
    setIdle();
}

void VitalsService::onWeight(double w)
{
    if(state!=State::Weight) return;

    if(m_repo && m_sessionId > 0)
        m_repo->saveWeight(m_sessionId,w);

    emit weightReady(w);
    setIdle();
}

void VitalsService::onHeight(double h)
{
    if(state!=State::Height) return;

    if(m_repo && m_sessionId > 0)
        m_repo->saveHeight(m_sessionId,int(h));

    emit heightReady(int(h));
    setIdle();
}

// ---------------- INTERNAL ----------------

void VitalsService::setIdle()
{
    state=State::Idle;
    timeout.stop();
}

void VitalsService::startTimeout()
{
    //timeout.start(20000);
    timeout.start(50000);
}

void VitalsService::setRepository(VitalsRepository* repo)
{
    m_repo = repo;
}
//talsModel VitalsService::currentVitals() const
//
    
    //  VitalsModel currentVitals;
    //  if(m_repo && m_sessionId > 0)
    //  {
    //      currentVitals = m_repo->getVitals(m_sessionId);
    //  }
    //turn currentVitals;
//