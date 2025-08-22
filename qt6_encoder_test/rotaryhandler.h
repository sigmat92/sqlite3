#ifndef ROTARYHANDLER_H
#define ROTARYHANDLER_H

#include <QObject>
#include <QString>

class RotaryHandler : public QObject
{
    Q_OBJECT
public:
    explicit RotaryHandler(const QString &rotaryDevice, const QString &switchDevice, QObject *parent = nullptr);

public slots:
    void processEvents();

signals:
    void rotated(int delta);
    void switchChanged(bool pressed);

private:
    QString rotaryDevicePath;
    QString switchDevicePath;
};

#endif // ROTARYHANDLER_H

