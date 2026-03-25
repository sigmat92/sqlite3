#pragma once
#include <QObject>
#include <QByteArray>

class ProtocolParser : public QObject {
    Q_OBJECT
public:
    explicit ProtocolParser(QObject* parent = nullptr);
    void feed(const QByteArray& data);

signals:
    void temperatureReceived(double value, char unit);
    void spo2Received(int spo2, int pulse);
    void nibpReceived(int sys, int dia, int pulse);
    void weightReceived(double value);
    void heightReceived(double value);

private:
    QByteArray buffer;
    void parseFrames();
};