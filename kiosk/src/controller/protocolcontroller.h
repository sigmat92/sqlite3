/*
#pragma once

#include <QObject>
#include <QByteArray>

class UartDevice;
class ProtocolParser;

class ProtocolController : public QObject
{
    Q_OBJECT

public:
    explicit ProtocolController(UartDevice* uart,
                                ProtocolParser* parser,
                                QObject* parent = nullptr);

    // measurement requests
    void requestTemperature();
    void requestSpo2();
    void requestWeight();
    void requestHeight();
    void requestNibp();

private:
    UartDevice* uart;
    ProtocolParser* parser;

    void sendWrappedCommand(quint8 cmd);
};
*/

#pragma once

#include <QObject>
#include <QByteArray>

class UartDevice;
class ProtocolParser;

class ProtocolController : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolController(UartDevice* uart,
                                ProtocolParser* parser,
                                QObject* parent = nullptr);

    void requestTemperature();
    void requestWeight();
    void requestSpo2();
    void setIdle();

signals:
    // RAW signals → VitalsService
    void temperatureRaw(double value, char unit);
    void spo2Raw(int spo2, int pulse);
    void weightRaw(double weight);
    void heightRaw(int height);
    void nibpRaw(int sys, int dia, int map);

private:
    UartDevice* uart{nullptr};
    ProtocolParser* parser{nullptr};
};
