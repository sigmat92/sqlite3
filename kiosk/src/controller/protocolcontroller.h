#pragma once
#include <QObject>
#include <QTimer>
#include "platform/uart/uartdevice.h"
#include "controller/protocolparser.h"
#include "model/vitalsmodel.h"

class UartDevice;
class ProtocolParser;
class VitalsModel;

class ProtocolController : public QObject
{
    Q_OBJECT
public:
	explicit ProtocolController(
        UartDevice *uart,
        ProtocolParser *parser,
        VitalsModel *vitals,
        QObject *parent = nullptr
    );
    void requestTemperature();
    void temperature(float temp);  
    void start();
    void stop();

private slots:
    void poll();

private:
    UartDevice *uart;
    ProtocolParser *parser;
    VitalsModel *vitals;

    QTimer timer;
};

