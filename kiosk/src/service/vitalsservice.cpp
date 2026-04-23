#include "vitalsservice.h"

#include "storage/vitalsrepository.h"   
#include <QDebug>

VitalsService::VitalsService(QObject* parent)
    : QObject(parent)
{
    timeout.setSingleShot(true);

    connect(&timeout, &QTimer::timeout, this, [this]() {
        qDebug() << "Timeout! Stopping safely";

        // send STOP if NIBP running
        if (state == State::Nibp)
        {
            //emit sendCommand(QByteArray::fromHex("96AAF50100"));
        }

        setIdle();
    });
}

/* ---------------- SESSION ---------------- */

void VitalsService::setSessionId(int id)
{
    qDebug() << "Session set:" << id;
    m_sessionId = id;
}

int VitalsService::sessionId() const   // FIX
{
    return m_sessionId;
}

void VitalsService::setRepository(VitalsRepository* repo)
{
    m_repo = repo;
}

/* ---------------- REQUESTS ---------------- */

void VitalsService::requestTemperature()
{
    if (state != State::Idle) return;

    state = State::Temp;
    emit sendCommand(QByteArray("\x96\xAA\x54", 3));

    startTimeout();
}

void VitalsService::requestSpo2()
{
    if (state != State::Idle) return;

    state = State::Spo2;

    qDebug() << "Request SPO2 session:" << m_sessionId;

    emit sendCommand(QByteArray("\x96\xAA\xF4", 3));

    startTimeout();
}

void VitalsService::requestNibp()
{
    if (state != State::Idle) return;

    state = State::Nibp;

    qDebug() << "Request NIBP session:" << m_sessionId;

    emit sendCommand(QByteArray("\x96\xAA\xF5\x01\x01", 5));

    startTimeout();   // timer starts HERE
}

void VitalsService::requestWeight()
{
    if (state != State::Idle) return;

    state = State::Weight;

    emit sendCommand(QByteArray("\x96\xAA\xF8", 3));

    startTimeout();
}

void VitalsService::requestHeight()
{
    if (state != State::Idle) return;

    state = State::Height;

    emit sendCommand(QByteArray("\x96\xAA\xF7", 3));

    startTimeout();
}

/* ---------------- RESPONSES ---------------- */

void VitalsService::onTemperature(double v, char unit)
{
    if (state != State::Temp) return;
    if (v <= 1.0) return;

    if (m_repo && m_sessionId > 0)
        m_repo->saveTemperature(m_sessionId, v);

    emit temperatureReady(v, unit);
    setIdle();
}

void VitalsService::onSpo2(int s, int p)
{
    if (state != State::Spo2) return;

    if (m_repo && m_sessionId > 0)
        m_repo->saveSpO2(m_sessionId, s, p);

    emit spo2Ready(s, p);
    setIdle();
}

void VitalsService::onNibpPressure(int pressure)
{
    if (state != State::Nibp) return;

    qDebug() << "[VS] Pressure update:" << pressure;

    emit nibpPressure(pressure);

    // IMPORTANT: do NOT stop here
    // keeps measurement running
}
void VitalsService::onNibp(int sys,int dia,int map)
{
    if(state!=State::Nibp) return;

    //if(m_repo && m_sessionId > 0)
    //    m_repo->saveNIBP(m_sessionId,sys,dia);

    emit nibpReady(sys,dia,0);
    setIdle();
}
/*
void VitalsService::onNibp(int sys, int dia, int status)
{
    if (state != State::Nibp) return;

    static int finalCount = 0;

    // ignore garbage
    if (sys == 0 && dia == 0)
        return;

    finalCount++;

    qDebug() << "[VS] FINAL COUNT:" << finalCount;

    // wait stable frames
    if (finalCount < 3)
        return;

    if (m_repo && m_sessionId > 0)
        m_repo->saveNIBP(m_sessionId, sys, dia);

    emit nibpReady(sys, dia, 0);

    // STOP device
    emit sendCommand(QByteArray::fromHex("96AAF50100"));

    finalCount = 0;
    setIdle();
}
*/
void VitalsService::onWeight(double w)
{
    if (state != State::Weight) return;

    if (m_repo && m_sessionId > 0)
        m_repo->saveWeight(m_sessionId, w);

    emit weightReady(w);
    setIdle();
}

void VitalsService::onHeight(double h)
{
    if (state != State::Height) return;

    if (m_repo && m_sessionId > 0)
        m_repo->saveHeight(m_sessionId, int(h));

    emit heightReady(int(h));
    setIdle();
}

/* ---------------- INTERNAL ---------------- */

void VitalsService::setIdle()
{
    state = State::Idle;
    timeout.stop();

    qDebug() << "[VS] Back to IDLE";
}

void VitalsService::startTimeout()
{
    timeout.start(50000);   // 50 sec (safe for NIBP)
}