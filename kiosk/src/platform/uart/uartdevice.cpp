#include "uartdevice.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <QDebug>

UartDevice::UartDevice(QObject* parent) : QObject(parent) {}

bool UartDevice::open(const QString& dev, int baud)
{
    m_fd = ::open(dev.toLocal8Bit().constData(),
                  O_RDWR | O_NOCTTY);   // | O_NONBLOCK for async read, but we use QSocketNotifier instead
    if (m_fd < 0) {
        qWarning() << "UART open failed";
        return false;
    }

    struct termios tio;
    if (tcgetattr(m_fd, &tio) != 0) {
        qWarning() << "tcgetattr failed";
        return false;
    }

    // RAW mode (pySerial equivalent)
    cfmakeraw(&tio);

    speed_t speed = B9600;
    switch (baud) {
    case 9600:   speed = B9600; break;
    case 19200:  speed = B19200; break;
    case 38400:  speed = B38400; break;
    case 57600:  speed = B57600; break;
    case 115200: speed = B115200; break;
    }

    cfsetispeed(&tio, speed);
    cfsetospeed(&tio, speed);

    // 8N1
    tio.c_cflag &= ~PARENB;
    tio.c_cflag &= ~CSTOPB;
    tio.c_cflag &= ~CSIZE;
    tio.c_cflag |= CS8;
    tio.c_cflag |= (CLOCAL | CREAD);

    // IMPORTANT for USB-CDC
    tio.c_cc[VMIN]  = 1;
    tio.c_cc[VTIME] = 0;

    tcflush(m_fd, TCIFLUSH);
    tcsetattr(m_fd, TCSANOW, &tio);

    // 🔥 notifier AFTER termios
    m_notifier = new QSocketNotifier(m_fd,
                                     QSocketNotifier::Read,
                                     this);
    connect(m_notifier, &QSocketNotifier::activated,
            this, &UartDevice::onReadyRead);

    qDebug() << "UART opened:" << dev << "baud" << baud;
    return true;
}
/*
void UartDevice::writeBytes(const QByteArray& data)
{
    if (m_fd >= 0) {
        ::write(m_fd, data.constData(), data.size());
    }
}
*/
void UartDevice::writeBytes(const QByteArray& data)
{
    if (m_fd < 0)
        return;

    ssize_t written = ::write(m_fd, data.constData(), data.size());
    if (written < 0) {
        qWarning() << "UART write failed";
    } else if (written != data.size()) {
        qWarning() << "UART partial write:" << written << "/" << data.size();
    }
}


void UartDevice::onReadyRead()
{
    qDebug() << "UART notifier activated";

    char buf[256];
    int n = ::read(m_fd, buf, sizeof(buf));
    if (n > 0) {
        QByteArray data(buf, n);
        qDebug() << "UART RX HEX:" << data.toHex(' ');
        emit bytesReceived(data);
    }
}

