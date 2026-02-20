#pragma once
#include <QObject>
#include <QSocketNotifier>

class UartDevice : public QObject
{
    Q_OBJECT
public:
    explicit UartDevice(QObject* parent = nullptr);
    bool open(const QString& dev, int baud);
    void writeBytes(const QByteArray& data);
    void send(const QByteArray& data) { writeBytes(data); }

signals:
    void bytesReceived(const QByteArray& data);

private slots:
    void onReadyRead();

private:
    int m_fd{-1};
    QSocketNotifier* m_notifier{nullptr};
};

