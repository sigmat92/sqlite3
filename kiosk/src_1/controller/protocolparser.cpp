#include "protocolparser.h"
#include <QDebug>

ProtocolParser::ProtocolParser(QObject* parent)
    : QObject(parent)
{
}

void ProtocolParser::feed(const QByteArray& data)
{
    buffer.append(data);
    parseFrames();
}

void ProtocolParser::parseFrames()
{
    while (true) {
        int start = buffer.indexOf(char(0xFB));
        if (start < 0) return;

        int end = buffer.indexOf(char(0xFB), start + 1);
        if (end < 0) return;

        QByteArray frame = buffer.mid(start, end - start + 1);
        buffer.remove(0, end + 1);

        qDebug() << "Parser frame:" << frame.toHex(' ');

        // ---- Ignore IDLE frames ----
        if (frame.size() == 5 && frame[3] == char(0x00)) {
            continue;
        }

        // ---- Decode TEMPERATURE (exact Python mapping) ----
        //if (frame.size() >= 10 && quint8(frame[4]) == 0x06) {
        if (frame.size() >= 10 && quint8(frame[3]) == 0x06) {
            int tempInt  = quint8(frame[6]);
            int tempFrac = quint8(frame[7]);
            char unit    = char(frame[8]);

            double tempValue = tempInt + (tempFrac / 10.0);
	    qDebug() << "Decoded temperature:" << tempValue << unit;
            //emit temperature(tempValue, unit);
            //return; //  stop after first valid measurement
            emit temperature(tempValue, unit);
            buffer.clear();          // flush old stream data
            break;                   // exit loop, not function

        }
    }
}

  
