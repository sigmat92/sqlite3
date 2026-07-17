#pragma once

#include <QObject>
#include <atomic>

class RotaryHandler : public QObject
{
    Q_OBJECT

public:
    explicit RotaryHandler(const QString &rotaryDevice,
                           const QString &switchDevice,
                           QObject *parent = nullptr);

public slots:
    void processEvents();
    void stop();

signals:
    void rotatedLeft();
    void rotatedRight();
    void pressed();

    //void mutePressed();
    //void freezePressed();

private:
    QString rotaryDevicePath;
    QString switchDevicePath;

    std::atomic<bool> m_running{true};
};
