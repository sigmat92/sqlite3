#pragma once
#include <QObject>
#include <QTimer>

class UartDevice;
class ProtocolParser;
class VitalsModel;

class ProtocolController : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolController(UartDevice* uart,
                                ProtocolParser* parser,
                                VitalsModel* vitals,
                                QObject* parent = nullptr);

public slots:
    void requestTemperature();
    void setIdle();   // 

private:
    enum class MeasureState {
        Idle,
        Waiting
    };

    MeasureState state{MeasureState::Idle};

    UartDevice* uart;
    ProtocolParser* parser;
    VitalsModel* vitals;
};

