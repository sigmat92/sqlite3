#pragma once

#include <QObject>
#include <QTimer>

class GPIOKeyHandler : public QObject
{
    Q_OBJECT

public:
    explicit GPIOKeyHandler(QObject *parent = nullptr);

public slots:
    void processEvents();
    void stop();

signals:
    void mutePressed();
    void nibpPressed();
    void freezePressed();
    void printPressed();
    void menuPressed();

private:
    bool m_running = true;

    int lastMute    = 0;
    int lastNibp    = 0;
    int lastFreeze  = 0;
    int lastPrint   = 0;
    int lastMenu    = 0;

    bool readGPIO(int gpio);
};