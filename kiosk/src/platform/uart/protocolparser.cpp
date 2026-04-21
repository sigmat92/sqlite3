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
        // 🔥 RESYNC FILTER (CRITICAL)
        if (byte == 0xF2 || byte == 0xF4 || byte == 0xF5 ||
            byte == 0xF7 || byte == 0xF8 || byte == 0xFA || byte == 0xFB)
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
        if (payloadIndex < sizeof(payload))
            payload[payloadIndex++] = byte;
        else
        {
            state = WAIT_CTRL;
            return;
        }

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
    /* -------- PULSE -------- */
    if (ctrl == 0xF2 && nob == 1)
    {
        int pulse = payload[0];
        if (pulse < 30 || pulse > 239)
            pulse = 0;

        lastPulse = pulse;
    }

    /* -------- SPO2 -------- */
    else if (ctrl == 0xF4 && nob == 1)
    {
        int spo2 = payload[0];
        if (spo2 > 100)
            spo2 = 0;

        lastSpo2 = spo2;
    }

    /* -------- EMIT SPO2 -------- */
    if (lastSpo2 >= 0 && lastPulse >= 0)
    {
        emit spo2Received(lastSpo2, lastPulse);
        lastSpo2 = -1;
    }

    /* -------- NIBP -------- */
    else if (ctrl == 0xF5)
    {
        quint8 len  = nob;
        quint8 mode = payload[0];

        /* PRESSURE */
        if (mode == 0x01 && len >= 3)
        {
            int pressure = (payload[1] * 128) | payload[2];

            qDebug() << "[NIBP] Pressure:" << pressure;
            emit nibpPressure(pressure);
            return;
        }

        /* FINAL */
        if (mode == 0x00)
        {
            int sys = 0;
            int dia = 0;
            int mean = 0;
            int err = 0;

            if (len == 6)
            {
                sys  = payload[1]*128 + payload[2];
                dia  = payload[3];
                mean = payload[4];
                err  = payload[5];
            }
            else if (len == 4)
            {
                sys = payload[1]*128 + payload[2];
                dia = payload[3];
            }
            else
            {
                return;
            }

            if (sys == 0 && dia == 0)
                return;

            qDebug() << "[FINAL RAW]"
                     << "SYS:" << sys
                     << "DIA:" << dia
                     << "MEAN:" << mean
                     << "ERR:" << err;

            emit nibpReceived(sys, dia, mode);
            return;
        }
    }

    /* -------- TEMP -------- */
    else if (ctrl == 0xFA && nob == 3)
    {
        double temp = payload[0] + payload[1] / 10.0;
        char unit = static_cast<char>(payload[2]);

        emit temperatureReceived(temp, unit);
    }

    /* -------- WEIGHT -------- */
    else if (ctrl == 0xF8 && nob >= 2)
    {
        double weight = payload[0] + payload[1];
        emit weightReceived(weight);
    }

    /* -------- HEIGHT -------- */
    else if (ctrl == 0xF7 && nob >= 2)
    {
        int height = payload[1];
        if (height != 0x80)
            emit heightReceived(height);
    }
}