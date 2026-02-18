#include "protocolcontroller.h"
#include "platform/uart/uartdevice.h"
#include "controller/protocolparser.h"

#include <QDebug>
#include <QTimer>

enum class MeasureState { Idle, Waiting };
static MeasureState state{MeasureState::Idle};

ProtocolController::ProtocolController(UartDevice* uart,
                                       ProtocolParser* parser,
                                       QObject* parent)
    : QObject(parent),
      uart(uart),
      parser(parser)
{
    // UART → Parser
    QObject::connect(uart, &UartDevice::bytesReceived,
                     parser, &ProtocolParser::feed);

    // Parser → RAW temperature only (others not implemented yet)
    QObject::connect(parser, &ProtocolParser::temperature,
                     this, [this](double value, char unit) {
        qDebug() << "ProtocolController RAW temperature:" << value << unit;
        emit temperatureRaw(value, unit);
        setIdle();
    });
}

void ProtocolController::requestTemperature()
{
    if (state != MeasureState::Idle)
        return;

    state = MeasureState::Waiting;

    // IDLE MODE
    QByteArray idleCmd;
    idleCmd.append(char(0x96));
    idleCmd.append(char(0xAA));
    idleCmd.append(char(0xFB));
    idleCmd.append(char(0x49));
    idleCmd.append(char(0x73));
    uart->send(idleCmd);

    // Delay → Temperature request
    QTimer::singleShot(50, this, [this]() {
        QByteArray cmd;
        cmd.append(char(0x96));
        cmd.append(char(0xAA));
        cmd.append(char(0x54));   // TEMP REQUEST
        uart->send(cmd);
    });
}

void ProtocolController::setIdle()
{
    qDebug() << "ProtocolController: back to IDLE";
    state = MeasureState::Idle;
}

/*
#include "protocolcontroller.h"
#include "platform/uart/uartdevice.h"
#include "controller/protocolparser.h"

#include <QDebug>
#include <QTimer>

enum class MeasureState { Idle, Waiting };
static MeasureState state{MeasureState::Idle};

ProtocolController::ProtocolController(UartDevice* uart,
                                       ProtocolParser* parser,
                                       QObject* parent)
    : QObject(parent),
      uart(uart),
      parser(parser)
{
    // UART → Parser
    QObject::connect(uart, &UartDevice::bytesReceived,
                     parser, &ProtocolParser::feed);

    // Parser → RAW signals (NO MODEL HERE)
    QObject::connect(parser, &ProtocolParser::temperature,
                     this, [this](double value, char unit) {
        qDebug() << "ProtocolController RAW temperature:" << value << unit;
        emit temperatureRaw(value, unit);
        setIdle();
    });

    QObject::connect(parser, &ProtocolParser::spo2,
                     this, [this](int spo2, int pulse) {
        emit spo2Raw(spo2, pulse);
        setIdle();
    });

    QObject::connect(parser, &ProtocolParser::weight,
                     this, [this](double weight) {
        emit weightRaw(weight);
        setIdle();
    });

    QObject::connect(parser, &ProtocolParser::height,
                     this, [this](int height) {
        emit heightRaw(height);
        setIdle();
    });

    QObject::connect(parser, &ProtocolParser::nibp,
                     this, [this](int sys, int dia, int map) {
        emit nibpRaw(sys, dia, map);
        setIdle();
    });
}

void ProtocolController::requestTemperature()
{
    if (state != MeasureState::Idle)
        return;

    state = MeasureState::Waiting;

    // IDLE MODE
    QByteArray idleCmd;
    idleCmd.append(char(0x96));
    idleCmd.append(char(0xAA));
    idleCmd.append(char(0xFB));
    idleCmd.append(char(0x49));
    idleCmd.append(char(0x73));
    uart->send(idleCmd);

    // Delay → Temperature request
    QTimer::singleShot(50, this, [this]() {
        QByteArray cmd;
        cmd.append(char(0x96));
        cmd.append(char(0xAA));
        cmd.append(char(0x54));   // TEMP REQUEST
        uart->send(cmd);
    });
}

void ProtocolController::setIdle()
{
    qDebug() << "ProtocolController: back to IDLE";
    state = MeasureState::Idle;
}
*/