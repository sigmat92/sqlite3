#include "uartdevice.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <QDebug>

UartDevice::UartDevice(QObject* parent)
    : QObject(parent), m_fd(-1), m_notifier(nullptr)
{
}

bool UartDevice::open(const QString& dev, int baud)
{
    m_fd = ::open(dev.toLocal8Bit().constData(), O_RDWR | O_NOCTTY);
    if (m_fd < 0) {
        qWarning() << "UART open failed";
        return false;
    }

    struct termios tio;
    tcgetattr(m_fd, &tio);

    cfmakeraw(&tio);

    speed_t speed = B9600;
    if (baud == 115200) speed = B115200;

    cfsetispeed(&tio, speed);
    cfsetospeed(&tio, speed);

    tio.c_cflag |= (CLOCAL | CREAD);
    tio.c_cc[VMIN] = 1;
    tio.c_cc[VTIME] = 0;

    tcsetattr(m_fd, TCSANOW, &tio);

    m_notifier = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
    connect(m_notifier,
            &QSocketNotifier::activated,
            this,
            &UartDevice::onReadyRead);

    qDebug() << "UART opened:" << dev;

    return true;
}

void UartDevice::send(const QByteArray& data)
{
    if (m_fd < 0)
        return;

    ssize_t written = ::write(m_fd, data.constData(), data.size());

    if (written < 0)
    {
        qWarning() << "UART write failed";
    }
    else if (written != data.size())
    {
        qWarning() << "UART partial write:" << written << "/" << data.size();
    }
}

void UartDevice::onReadyRead()
{
    
    char buf[256];
    int n = ::read(m_fd, buf, sizeof(buf));

    if (n > 0) {
        QByteArray data(buf, n);
        //qDebug() << "UART RX:" << data.toHex(' ');
        emit bytesReceived(data);
    }
}

