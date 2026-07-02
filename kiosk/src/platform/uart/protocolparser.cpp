#include "protocolparser.h"
#include <QDebug>

ProtocolParser::ProtocolParser(QObject* parent)
    : QObject(parent),
      state(WAIT_CTRL),
      ctrl(0),
      nob(0),
      payloadIndex(0)
{
}

void ProtocolParser::feed(const QByteArray& data)
{
    for (auto byte : data)
        parseByte(static_cast<quint8>(byte));
}

/* ================= STATE MACHINE ================= */

void ProtocolParser::parseByte(quint8 byte)
{
    qDebug() << "[RX]" << QString::number(byte, 16);

    switch (state)
    {
    case WAIT_CTRL:
        // HARD RESYNC FILTER
        if (byte == 0xF2 || byte == 0xF4 || byte == 0xF5 ||
            byte == 0xF7 || byte == 0xF8 || byte == 0xFA)
        {
            ctrl = byte;
            state = WAIT_NOB;
        }
        break;

    case WAIT_NOB:
        nob = byte;

        if (nob == 0 || nob > sizeof(payload))
        {
            state = WAIT_CTRL;
            return;
        }

        payloadIndex = 0;
        state = READ_PAYLOAD;
        break;

    case READ_PAYLOAD:
        payload[payloadIndex++] = byte;

        if (payloadIndex >= nob)
        {
            decodeFrame();
            state = WAIT_CTRL;
        }
        break;
    }
}

/* ================= DECODER ================= */

void ProtocolParser::decodeFrame()
{
    switch (ctrl)
    {
        case 0xF2:
            decodePulse();
            break;

        case 0xF4:
            decodeSpo2();
            break;

        case 0xF5:
            decodeNibp();
            break;

        case 0xF7:
            decodeHeight();
            break;

        case 0xF8:
            decodeWeight();
            break;

        case 0xFA:
            decodeTemperature();
            break;

        default:
            qDebug() << "[Protocol] Unknown CTRL:"
                     << Qt::hex << ctrl;
            break;
    }
}
// -------- SPO2-------- 
void ProtocolParser::decodeSpo2()
{
    if (nob != 1)
        return;

    lastSpo2 = (payload[0] > 100)
                 ? 0
                 : payload[0];

    emitSpo2IfComplete();
}
// -------- PULSE -------- 
void ProtocolParser::decodePulse()
{
    if (nob != 1)
        return;

    int pulse = payload[0];

    lastPulse =
            (pulse < 30 || pulse > 239)
            ? 0
            : pulse;

    emitSpo2IfComplete();
}
//emitSpo2IfComplete() is called after both 
void ProtocolParser::emitSpo2IfComplete()
{
    if (lastSpo2 < 0 ||
        lastPulse < 0)
    {
        return;
    }

    emit spo2Received(lastSpo2,
                      lastPulse);

    lastSpo2  = -1;
    lastPulse = -1;
}
// -------- NIBP / Pressure-------- 
void ProtocolParser::decodeNibp()
{
    if (nob < 1)
        return;

    quint8 mode = payload[0];

    switch (mode)
    {
        case 0x01:      // Live Pressure
        {
            if (nob < 3)
                return;

            int pressure =
                    (payload[1] << 7) |
                     payload[2];

            emit nibpPressure(pressure);
            break;
        }

        case 0x00:      // Final Result
        {
            if (nob != 4 &&
                nob != 6)
            {
                return;
            }

            int sys =
                    (payload[1] << 7) |
                     payload[2];

            int dia = payload[3];

            if (sys == 0 &&
                dia == 0)
            {
                return;
            }

            emit nibpReceived(sys,
                              dia,
                              mode);

            break;
        }

        default:
            break;
    }
}
// -------- TEMP -------- 
void ProtocolParser::decodeTemperature()
{
    if (nob != 3)
        return;

    emit temperatureReceived(
            payload[0] +
            payload[1] / 10.0,
            static_cast<char>(payload[2]));
}
// -------- WEIGHT -------- 
void ProtocolParser::decodeWeight()
{
    if (nob < 2)
        return;

    emit weightReceived(
            payload[0] +
            payload[1]);
}
// -------- HEIGHT -------- 
void ProtocolParser::decodeHeight()
{
    if (nob < 2)
        return;

    if (payload[1] == 0x80)
        return;

    emit heightReceived(payload[1]);
}
/*old working design implementation
void ProtocolParser::decodeFrame()
{
    // -------- SPO2 -------- 
    if (ctrl == 0xF4 && nob == 1)
    {
        lastSpo2 = payload[0] > 100 ? 0 : payload[0];
    }

    // -------- PULSE -------- 
    else if (ctrl == 0xF2 && nob == 1)
    {
        int p = payload[0];
        lastPulse = (p < 30 || p > 239) ? 0 : p;
    }

    if (lastSpo2 >= 0 && lastPulse >= 0)
    {
        emit spo2Received(lastSpo2, lastPulse);
        lastSpo2 = -1;
    }

    // -------- NIBP -------- 
    else if (ctrl == 0xF5)
    {
        quint8 len  = nob;
        quint8 mode = payload[0];

        // PRESSURE
        if (mode == 0x01 && len >= 3)
        {
            int pressure = (payload[1] * 128) | payload[2];
            qDebug() << "[NIBP] Pressure:" << pressure;
            emit nibpPressure(pressure);
            return;
        }

        // FINAL
        if (mode == 0x00)
        {
            int sys = 0, dia = 0;

            if (len == 6 || len == 4)
            {
                sys = payload[1]*128 + payload[2];
                dia = payload[3];
            }
            else return;

            if (sys == 0 && dia == 0)
                return;

            qDebug() << "[FINAL RAW]" << sys << dia;

            emit nibpReceived(sys, dia, mode);
        }
    }

    // -------- TEMP -------- 
    else if (ctrl == 0xFA && nob == 3)
    {
        emit temperatureReceived(payload[0] + payload[1]/10.0,
                                 static_cast<char>(payload[2]));
    }

    // -------- WEIGHT -------- 
    else if (ctrl == 0xF8 && nob >= 2)
    {
        emit weightReceived(payload[0] + payload[1]);
    }

    // -------- HEIGHT -------- 
    else if (ctrl == 0xF7 && nob >= 2)
    {
        if (payload[1] != 0x80)
            emit heightReceived(payload[1]);
    }
}
*/