#include "protocolcontroller.h"

ProtocolController::ProtocolController(
            UartDevice *uart,
    		ProtocolParser *parser,
    		VitalsModel *vitals,
    		QObject *parent)
    		: QObject(parent),
      		uart(uart),
      		parser(parser),
      		vitals(vitals)
{
    QObject::connect(uart, &UartDevice::bytesReceived,
                     parser, &ProtocolParser::feed);

    QObject::connect(parser, &ProtocolParser::spo2,
                     vitals, &VitalsModel::setSpo2);

    QObject::connect(parser, &ProtocolParser::pulseRate,
                     vitals, &VitalsModel::setPulseRate);

    QObject::connect(parser, &ProtocolParser::temperature,
                     vitals, &VitalsModel::setTemperature);

    timer.setInterval(1000);
    QObject::connect(&timer, &QTimer::timeout,
                     this, &ProtocolController::poll);

}

void ProtocolController::start()
{
    timer.start();
}

void ProtocolController::poll()
{
    QByteArray spo2Cmd;
    spo2Cmd.append(char(0x96));
    spo2Cmd.append(char(0xAA));
    spo2Cmd.append(char(0xF4));
    uart->send(spo2Cmd);

    QByteArray tempCmd;
    tempCmd.append(char(0x96));
    tempCmd.append(char(0xAA));
    tempCmd.append(char(0x54));   // TEMP request
    uart->send(tempCmd);
}

void ProtocolController::requestTemperature()
{
    if (!uart)
        return;

    // TEMPERATURE REQUEST: [0x96, 0xAA, 0x54]
    QByteArray cmd;
    cmd.append(char(0x96));
    cmd.append(char(0xAA));
    cmd.append(char(0x54));

    uart->send(cmd);
}

