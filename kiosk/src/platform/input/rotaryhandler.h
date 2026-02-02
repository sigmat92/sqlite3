#pragma once
#include <QObject>

class RotaryHandler : public QObject
{
    Q_OBJECT
public:
    explicit RotaryHandler(const QString& rotaryDevice,
                           const QString& switchDevice,
                           QObject* parent = nullptr);

public slots:
    void processEvents();
    void stop();

signals:
    void rotatedLeft();
    void rotatedRight();
    void pressed();

private:
    QString rotaryDevicePath;
    QString switchDevicePath;
    bool m_running{true};
};

