

#pragma once

#include <QObject>
#include <QSocketNotifier>
#include <QByteArray>

class UartDevice : public QObject
{
    Q_OBJECT

public:
    explicit UartDevice(QObject* parent = nullptr);

    bool open(const QString& dev, int baud);
    void send(const QByteArray& data);
    void write(const QByteArray& data);
    void flush();

signals:
    void bytesReceived(const QByteArray& data);

private slots:
    void onReadyRead();

private:
    int m_fd;
    QSocketNotifier* m_notifier;
};