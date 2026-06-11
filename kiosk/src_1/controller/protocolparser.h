
#pragma once
#include <QObject>
#include <QByteArray>

class ProtocolParser : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolParser(QObject* parent = nullptr);

public slots:
    void feed(const QByteArray& data);

signals:
    
    void temperature(double value, char unit);
    void spo2(int spo2Percent, int pulseRate);

private:
    QByteArray buffer;
    void parseFrames();
};

