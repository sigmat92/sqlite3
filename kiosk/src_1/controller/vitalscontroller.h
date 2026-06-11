#include "vitalscontroller.h"

VitalsController::VitalsController(QObject* parent) : QObject(parent) {
    m_uart.open("/dev/ttyACM0", 9600);

    connect(&m_uart, &UartDevice::bytesReceived,
            &m_parser, &ProtocolParser::feed);

    connect(&m_parser, &ProtocolParser::spo2Updated,
            &m_model, &VitalsModel::setSpo2);

    connect(&m_parser, &ProtocolParser::temperatureUpdated,
            &m_model, &VitalsModel::setTemperature);
}

