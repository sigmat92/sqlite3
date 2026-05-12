#include "vitalsservice.h"
#include <QThread>
#include <QElapsedTimer>
#include "storage/vitalsrepository.h" 
#include <QDateTime>  
#include <QDebug>

VitalsService::VitalsService(QObject* parent)
    : QObject(parent)
{
    
    qRegisterMetaType<VitalsService::State>("VitalsService::State");
    
    timeout.setSingleShot(true);

    liveMeasureTimer.setSingleShot(true);

    connect(&liveMeasureTimer, &QTimer::timeout,
            this, [this]()
    {
        qDebug() << "[VS] Live measurement completed";

        setIdle();
    });

    connect(&timeout, &QTimer::timeout, this, [this]() {

        qDebug() << "Timeout! Stopping safely";

        if (state == State::Nibp)
        {
            emit sendCommand(QByteArray::fromHex("96AAF50100"));
        }

        setIdle();
    });
    //timeout.setSingleShot(true);

    //connect(&timeout, &QTimer::timeout, this, [this]() {
    //    qDebug() << "Timeout! Stopping safely";

        // send STOP if NIBP running
    //    if (state == State::Nibp)
    //    {
    //        emit sendCommand(QByteArray::fromHex("96AAF50100"));
    //    }

    //        setIdle();
    //});
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
    if (state != State::Idle)
        return;

    state = State::Temp;

    liveUpdateEnabled = true;

    emit sendCommand(QByteArray("\x96\xAA\x54", 3));

    liveMeasureTimer.start(20000);

    startTimeout();
    //if (state != State::Idle) return;

    //state = State::Temp;
    //emit sendCommand(QByteArray("\x96\xAA\x54", 3));

    //startTimeout();
}

void VitalsService::requestSpo2()
{
    if (state != State::Idle)
        return;

    state = State::Spo2;

    liveUpdateEnabled = true;

    emit sendCommand(QByteArray("\x96\xAA\xF4", 3));

    liveMeasureTimer.start(20000);

    startTimeout();
}
/*
void VitalsService::requestSpo2()
{
    if (state != State::Idle) return;

    state = State::Spo2;

    qDebug() << "Request SPO2 session:" << m_sessionId;

    emit sendCommand(QByteArray("\x96\xAA\xF4", 3));

    startTimeout();
}
*/
void VitalsService::requestNibp()
{
    if (state != State::Idle)
        return;

    state = State::Nibp;

    liveUpdateEnabled = true;

    emit sendCommand(QByteArray("\x96\xAA\xF5\x01\x01", 5));

    liveMeasureTimer.start(40000);

    startTimeout();
    //if (state != State::Idle) return;

    //state = State::Nibp;

    //qDebug() << "Request NIBP session:" << m_sessionId;

    //emit sendCommand(QByteArray("\x96\xAA\xF5\x01\x01", 5));

    //startTimeout();   // timer starts HERE
}

void VitalsService::requestWeight()
{
    if (state != State::Idle)
        return;

    state = State::Weight;

    liveUpdateEnabled = true;

    emit sendCommand(QByteArray("\x96\xAA\xF8", 3));

    liveMeasureTimer.start(20000);   
    //if (state != State::Idle) return;

    //state = State::Weight;

    //emit sendCommand(QByteArray("\x96\xAA\xF8", 3));

    //startTimeout();
}

void VitalsService::requestHeight()
{
    if (state != State::Idle)
        return;

    state = State::Height;

    liveUpdateEnabled = true;

    emit sendCommand(QByteArray("\x96\xAA\xF7", 3));

    liveMeasureTimer.start(20000);  
    //if (state != State::Idle) return;

    //state = State::Height;

    //emit sendCommand(QByteArray("\x96\xAA\xF7", 3));

    //startTimeout();
}

/* ---------------- RESPONSES ---------------- */

void VitalsService::onTemperature(double v, char unit)
{
    if (state != State::Temp) return;
    if (v <= 1.0) return;

    if (m_repo && m_sessionId > 0)
        m_repo->saveTemperature(m_sessionId, v);

    emit temperatureReady(v, unit);
    qDebug() << "[VS] LIVE TEMPERATURE:" << v << unit;
    //setIdle();
}

void VitalsService::onSpo2(int s, int p)
{
    if (state != State::Spo2) return;

    if (m_repo && m_sessionId > 0)
        m_repo->saveSpO2(m_sessionId, s, p);

    emit spo2Ready(s, p);
    qDebug() << "[VS] LIVE SPO2:" << s << p;
    //setIdle();
}

void VitalsService::onNibpPressure(int pressure)
{
    if (state != State::Nibp) return;

    //qDebug() << "[VS] Pressure update:" << pressure;

    emit nibpPressure(pressure);
    qDebug() << "[VS] LIVE NIBP PRESSURE:" << pressure;
    // IMPORTANT: do NOT stop here
    // keeps measurement running
}
void VitalsService::onNibp(int sys,int dia,int map)
{
    if(state!=State::Nibp) return;

    if(m_repo && m_sessionId > 0)
        m_repo->saveNIBP(m_sessionId,sys,dia);

    emit nibpReady(sys,dia,0);
    qDebug() << "[VS] LIVE NIBP:" << sys << dia << map;
    //setIdle();
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
    qDebug() << "[VS] LIVE WEIGHT:" << w;
    //setIdle();
}

void VitalsService::onHeight(double h)
{
    if (state != State::Height) return;

    if (m_repo && m_sessionId > 0)
        m_repo->saveHeight(m_sessionId, int(h));

    emit heightReady(int(h));
    qDebug() << "[VS] LIVE HEIGHT:" << int(h);
    //setIdle();
}

/* ---------------- INTERNAL ---------------- */

QByteArray VitalsService::idleCommand() const
{
    return QByteArray::fromRawData("\x96\xAA\xFB\x49\x73", 5);
}

void VitalsService::setIdle()
{
    State old = state;

    state = State::Idle;

    timeout.stop();

    liveMeasureTimer.stop();

    emit measurementFinished(old);

    emit sendCommand(idleCommand());

    qDebug() << "[VS] STATE -> IDLE";
}
/*
void VitalsService::setIdle()
{
    state = State::Idle;
    timeout.stop();

    emit sendCommand(idleCommand());

    qDebug() << "[VS] STATE -> IDLE";
}
*/
void VitalsService::startTimeout()
{
    timeout.start(40000);   // 40 sec (safe for NIBP)
}
QString VitalsService::buildPrintText(int sessionId, const QVariantMap& d)
{
    auto getD = [&](const QString& k){ return d.value(k, 0).toDouble(); };
    auto getI = [&](const QString& k){ return d.value(k, 0).toInt(); };
    auto getS = [&](const QString& k){ return d.value(k, "").toString(); };

    QString name   = getS("name");
    QString mobile = getS("mobile");
    QString gender = getS("gender");
    int age        = getI("age");

    double temp   = getD("temperature");
    double weight = getD("weight");
    int height    = getI("height");
    int spo2      = getI("spo2");
    int pulse     = getI("pulse");

    int sys = getI("systolic");
    int dia = getI("diastolic");

    QString farVision  = getS("farVision");
    QString nearVision = getS("nearVision");

    // ---------- DERIVED ----------
    double bmi = 0, bmr = 0, bsa = 0;

    if (height > 0 && weight > 0)
    {
        double h = height / 100.0;
        bmi = weight / (h * h);

        if (gender == "Male")
            bmr = 10*weight + 6.25*height - 5*age + 5;
        else
            bmr = 10*weight + 6.25*height - 5*age - 161;

        bsa = sqrt((height * weight) / 3600.0);
    }

    QString bmiAnalysis = "--";
    if (bmi > 0)
    {
        if (bmi < 18.5) bmiAnalysis = "Underweight";
        else if (bmi < 25) bmiAnalysis = "Normal";
        else if (bmi < 30) bmiAnalysis = "Overweight";
        else bmiAnalysis = "Obese";
    }

    QString text;

    text += "      CareNest Health Kiosk\n";
    text += "--------------------------------\n";

    text += QString("Session    : %1\n").arg(sessionId);
    text += QString("Date       : %1\n")
            .arg(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm"));

    text += "--------------------------------\n";

    text += QString("Name       : %1\n").arg(name.isEmpty() ? "--" : name);
    text += QString("Mobile     : %1\n").arg(mobile.isEmpty() ? "--" : mobile);
    text += QString("Age        : %1 yrs\n").arg(age > 0 ? QString::number(age) : "--");
    text += QString("Gender     : %1\n").arg(gender.isEmpty() ? "--" : gender);

    text += "--------------------------------\n";

    text += QString("Temperature: %1 F\n")
            .arg(temp > 0 ? QString::number(temp,'f',1) : "--");

    text += QString("Height     : %1 cm\n")
            .arg(height > 0 ? QString::number(height) : "--");

    text += QString("Weight     : %1 Kg\n")
            .arg(weight > 0 ? QString::number(weight,'f',1) : "--");

    text += QString("BP         : %1/%2 mmHg\n")
            .arg(sys > 0 ? QString::number(sys) : "--")
            .arg(dia > 0 ? QString::number(dia) : "--");

    text += QString("SPO2       : %1 %%\n")
            .arg(spo2 > 0 ? QString::number(spo2) : "--");

    text += QString("PulseRate  : %1\n")
            .arg(pulse > 0 ? QString::number(pulse) : "--");

    text += "--------------------------------\n";

    text += QString("BMI        : %1 Kg/m2\n")
            .arg(bmi > 0 ? QString::number(bmi,'f',1) : "--");

    text += QString("BMI Status : %1\n").arg(bmiAnalysis);

    text += QString("BMR        : %1 Kcal\n")
            .arg(bmr > 0 ? QString::number(bmr,'f',1) : "--");

    text += QString("BSA        : %1 m2\n")
            .arg(bsa > 0 ? QString::number(bsa,'f',2) : "--");

    text += "--------------------------------\n";

    text += QString("Far Vision : %1\n").arg(farVision.isEmpty() ? "--" : farVision);
    text += QString("Near Vision: %1\n").arg(nearVision.isEmpty() ? "--" : nearVision);

    text += "--------------------------------\n\n\n";

    qDebug() << "[VS] Built print text:\n" << text;

    return text;
}
void VitalsService::printResults(int sessionId,
                                 const QVariantMap& data)
{
    qDebug() << "[VS] Preparing to print...";

    QString text = buildPrintText(sessionId, data);

    // IMPORTANT
    text.replace("\n", "\r\n");

    // SHORTER RECEIPT
    // avoid giant packets
    if (text.length() > 220)
        text = text.left(220);

    QByteArray payload = text.toUtf8();

    QByteArray cmd;

    // HEADER
    cmd.append(char(0x96));
    cmd.append(char(0xAA));
    cmd.append(char(0xF6));

    // LENGTH = payload only
    quint16 len = payload.size();

    cmd.append(char(len & 0xFF));
    cmd.append(char((len >> 8) & 0xFF));

    // TEXT
    cmd.append(payload);

    // FEED PAPER
    cmd.append(char(0x1B));
    cmd.append(char(0x64));
    cmd.append(char(0x03));

    // END
    cmd.append(char(0x96));
    cmd.append(char(0xAA));
    cmd.append(char(0xFB));
    cmd.append(char(0x49));

    qDebug() << "[VS] PAYLOAD LEN:" << payload.size();
    qDebug() << "[VS] TOTAL TX:" << cmd.size();
    qDebug() << "[UART TX]" << cmd.toHex(' ');

    emit sendRaw(cmd);

    setIdle();
}


