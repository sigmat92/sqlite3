#pragma once

#include <QObject>
#include <QByteArray>

class ProtocolParser : public QObject
{
    Q_OBJECT

public:
    explicit ProtocolParser(QObject* parent = nullptr);

    void feed(const QByteArray& data);

signals:
    void spo2Received(int spo2, int pulse);
    void nibpPressure(int pressure);
    void nibpReceived(int sys, int dia, int status);
        
    void temperatureReceived(double temp, char unit);
    void weightReceived(double weight);
    void heightReceived(int height);

private:
    void parseByte(quint8 byte);
    void decodeFrame();

    enum State {
        WAIT_CTRL,
        WAIT_NOB,
        READ_PAYLOAD
    };

    State state;

    quint8 ctrl;
    quint8 nob;

    quint8 payload[16];
    int payloadIndex;

    int lastSpo2 = -1;
    int lastPulse = -1;
};