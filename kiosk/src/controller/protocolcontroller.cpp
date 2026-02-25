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

