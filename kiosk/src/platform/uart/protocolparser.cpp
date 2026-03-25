#include "protocolparser.h"
#include <QDebug>

ProtocolParser::ProtocolParser(QObject* parent)
    : QObject(parent) {}

void ProtocolParser::feed(const QByteArray& data)
{
    buffer.append(data);
    parseFrames();
}

void ProtocolParser::parseFrames()
{
    while (true)
    {
        int start = buffer.indexOf(char(0xFB));
        if (start < 0) return;

        int end = buffer.indexOf(char(0xFB), start + 1);
        if (end < 0) return;

        QByteArray frame = buffer.mid(start, end - start + 1);
        buffer.remove(0, end + 1);

        if (frame.size() < 5) continue;

        quint8 cmd = quint8(frame[3]);

        switch(cmd)
        {
        case 0x06: // TEMP
        {
            int t = quint8(frame[6]);
            int f = quint8(frame[7]);
            char unit = frame[8];
            double val = t + (f / 10.0);
            emit temperatureReceived(val, unit);
            break;
        }

        case 0x02: // SPO2
        {
            emit spo2Received(quint8(frame[5]),
                              quint8(frame[6]));
            break;
        }

        case 0x03: // NIBP
        {
            emit nibpReceived(quint8(frame[5]),
                              quint8(frame[6]),
                              quint8(frame[7]));
            break;
        }

        case 0x04: // WEIGHT
        {
            double w = quint8(frame[5]) +
                       quint8(frame[6]) / 10.0;
            emit weightReceived(w);
            break;
        }

        case 0x05: // HEIGHT
        {
            double h = quint8(frame[5]) +
                       quint8(frame[6]) / 10.0;
            emit heightReceived(h);
            break;
        }

        default:
            break;
        }
    }
}