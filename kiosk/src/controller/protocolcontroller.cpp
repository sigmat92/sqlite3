/*
#include "protocolcontroller.h"
#include <QTimer>

static QByteArray idleFrame()
{
    QByteArray idle;
    idle.append(char(0x96));
    idle.append(char(0xAA));
    idle.append(char(0xFB));
    idle.append(char(0x49));
    idle.append(char(0x73));
    return idle;
}

ProtocolController::ProtocolController(UartDevice* uart,
                                       ProtocolParser* parser,
                                       QObject* parent)
    : QObject(parent),
      uart(uart),
      parser(parser)
{
    connect(uart,
            &UartDevice::bytesReceived,
            parser,
            &ProtocolParser::feed);
}

void ProtocolController::sendWrappedCommand(quint8 cmd)
{
    // 1 Send IDLE first
    uart->send(idleFrame());

    // 2 Small delay for MCU sync
    QTimer::singleShot(40, this, [this, cmd]()
    {
        QByteArray frame;

        frame.append(char(0x96));
        frame.append(char(0xAA));
        frame.append(char(cmd));

        uart->send(frame);

        // 3 Return to IDLE
        QTimer::singleShot(40, this, [this]()
        {
            uart->send(idleFrame());
        });
    });
}

void ProtocolController::requestTemperature()
{
    sendWrappedCommand(0x54);
}

void ProtocolController::requestSpo2()
{
    sendWrappedCommand(0x53);
}

void ProtocolController::requestWeight()
{
    sendWrappedCommand(0x57);
}

void ProtocolController::requestHeight()
{
    sendWrappedCommand(0x48);
}

void ProtocolController::requestNibp()
{
    sendWrappedCommand(0x4E);
}
*/

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
    //QObject::connect(parser, &ProtocolParser::temperature,
    //                 this, [this](double value, char unit) {
    //    qDebug() << "ProtocolController RAW temperature:" << value << unit;
    //    emit temperatureRaw(value, unit);
    //    setIdle();
    //});

    QObject::connect(parser, &ProtocolParser::temperature,
                 this, [this](double value, char unit) {

    // Ignore invalid initial frames
    if (value <= 1.0)   // filters 0C and junk
        return;

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
void ProtocolController::requestSpo2()
{
    if (state != MeasureState::Idle)
        return;

    state = MeasureState::Waiting;

    QByteArray cmd;
    cmd.append(char(0x96));
    cmd.append(char(0xAA));
    cmd.append(char(0x53));   // SpO2 REQUEST
    uart->send(cmd);
}
void ProtocolController::setIdle()
{
    qDebug() << "ProtocolController: back to IDLE";
    state = MeasureState::Idle;
}

