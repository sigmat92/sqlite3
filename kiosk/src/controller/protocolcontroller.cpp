#include "protocolcontroller.h"
#include "platform/uart/uartdevice.h"
#include "controller/protocolparser.h"
#include "model/vitalsmodel.h"
#include <QDebug>
#include <QTimer>


enum class MeasureState { Idle, Waiting };
MeasureState state{MeasureState::Idle};
/*
enum class MeasureState {
    Idle,
    WaitingForTemperature
};

MeasureState state = MeasureState::Idle;
*/

ProtocolController::ProtocolController(UartDevice* uart,
                                       ProtocolParser* parser,
                                       VitalsModel* vitals,
                                       QObject* parent)
    : QObject(parent),
      uart(uart),
      parser(parser),
      vitals(vitals)
{
    QObject::connect(uart, &UartDevice::bytesReceived,
                     parser, &ProtocolParser::feed);

    QObject::connect(parser, &ProtocolParser::temperature,
                     vitals, &VitalsModel::setTemperature);
}

void ProtocolController::requestTemperature()
{
    if (state != MeasureState::Idle)
        return;

    state = MeasureState::Waiting;

    QByteArray idle;
    idle.append(char(0x96));
    idle.append(char(0xAA));
    idle.append(char(0xFB));
    idle.append(char(0x49));
    idle.append(char(0x73));
    uart->send(idle);

    QTimer::singleShot(50, this, [this]() {
        QByteArray cmd;
        cmd.append(char(0x96));
        cmd.append(char(0xAA));
        cmd.append(char(0x54));
        uart->send(cmd);
    });
}

void ProtocolController::setIdle()
{
	qDebug() << "ProtocolController: back to IDLE";
    state = MeasureState::Idle;
}

/*
void ProtocolController::requestTemperature()
{
    if (!uart)
        return;

    qDebug() << "ProtocolController: Sending IDLE";

    QByteArray idle;
    idle.append(char(0x96));
    idle.append(char(0xAA));
    idle.append(char(0xFB));
    idle.append(char(0x49));
    idle.append(char(0x73));
    uart->send(idle);

    QTimer::singleShot(50, this, [this]() {
        qDebug() << "ProtocolController: Sending TEMP command";

        QByteArray cmd;
        cmd.append(char(0x96));
        cmd.append(char(0xAA));
        cmd.append(char(0x54));
        uart->send(cmd);
    });
}
*/
/*
void ProtocolController::requestTemperature()
{
    if (state != MeasureState::Idle)
        return;

    state = MeasureState::WaitingForTemperature;

    qDebug() << "ProtocolController: Sending IDLE";

    QByteArray idle{ char(0x96), char(0xAA), char(0xFB), char(0x49), char(0x73) };
    uart->send(idle);

    QTimer::singleShot(50, this, [this]() {
        qDebug() << "ProtocolController: Sending TEMP command";
        QByteArray cmd{ char(0x96), char(0xAA), char(0x54) };
        uart->send(cmd);
    });
}
*/

/*
void ProtocolController::requestTemperature()
{
    qDebug() << "ProtocolController: Sending IDLE";

    QByteArray idle;
    idle.append(char(0x96));
    idle.append(char(0xAA));
    idle.append(char(0xFB));
    idle.append(char(0x49));
    idle.append(char(0x73));
    uart->send(idle);

    QTimer::singleShot(50, this, [this]() {
        qDebug() << "ProtocolController: Sending TEMP command";

        QByteArray cmd;
        cmd.append(char(0x96));
        cmd.append(char(0xAA));
        cmd.append(char(0x54));
        uart->send(cmd);
    });
}
*/
