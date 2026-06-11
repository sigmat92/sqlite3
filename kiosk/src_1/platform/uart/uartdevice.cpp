#include "uartdevice.h"

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <QDebug>

UartDevice::UartDevice(QObject* parent)
    : QObject(parent), m_fd(-1), m_notifier(nullptr)
{
}

bool UartDevice::open(const QString& dev, int baud)
{
    m_fd = ::open(dev.toLocal8Bit().constData(),
                  O_RDWR | O_NOCTTY | O_NONBLOCK);

    if (m_fd < 0)
    {
        qWarning() << "UART open failed";
        return false;
    }

    struct termios tio{};
    tcgetattr(m_fd, &tio);

    cfmakeraw(&tio);

    speed_t speed = (baud == 115200) ? B115200 : B9600;
    cfsetispeed(&tio, speed);
    cfsetospeed(&tio, speed);

    tio.c_cflag |= (CLOCAL | CREAD);

    // CRITICAL FIX (prevents hang)
    tio.c_cc[VMIN]  = 0;
    tio.c_cc[VTIME] = 1;  // 100ms batching

    tcsetattr(m_fd, TCSANOW, &tio);

    m_notifier = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);

    connect(m_notifier, &QSocketNotifier::activated,
            this, &UartDevice::onReadyRead);

    qDebug() << "UART opened:" << dev;
    return true;
}

void UartDevice::send(const QByteArray& data)
{
    if (m_fd < 0)
        return;

    ssize_t total = 0;

    while (total < data.size())
    {
        ssize_t n = ::write(m_fd,
                            data.constData() + total,
                            data.size() - total);

        if (n < 0)
        {
            if (errno == EAGAIN)
                continue;

            qWarning() << "UART write error:" << strerror(errno);
            return;
        }

        total += n;
    }

    ::tcdrain(m_fd); // ensure sent
}

void UartDevice::flush()
{
    if (m_fd >= 0)
        ::tcflush(m_fd, TCIOFLUSH);
}

void UartDevice::onReadyRead()
{
    if (m_fd < 0)
        return;

    char buf[256];

    // CRITICAL: drain fully
    while (true)
    {
        int n = ::read(m_fd, buf, sizeof(buf));

        if (n > 0)
        {
            QByteArray chunk(buf, n);
            qDebug() << "[UART RAW]" << chunk.toHex(' ');
            emit bytesReceived(chunk);
        }
        else
        {
            if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
                break;

            break;
        }
    }
}

void UartDevice::write(const QByteArray& data)
{
    qDebug() << "WRITE CALLED";   // ADD THIS

    if (m_fd < 0)
    {
        qWarning() << "UART write failed: device not open";
        return;
    }

    ssize_t written = ::write(m_fd, data.constData(), data.size());

    if (written < 0)
    {
        qWarning() << "UART write error";
    }
    else
    {
        qDebug() << "[UART TX]" << data.toHex(' ');
    }
}
