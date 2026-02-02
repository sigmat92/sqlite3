#include "uartdevice.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

UartDevice::UartDevice(QObject* parent) : QObject(parent) {}

bool UartDevice::open(const QString& dev, int baud) {
    m_fd = ::open(dev.toLocal8Bit(), O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (m_fd < 0) return false;

    termios tio{};
    tcgetattr(m_fd, &tio);

    cfsetispeed(&tio, B9600);
    cfsetospeed(&tio, B9600);

    tio.c_cflag = CS8 | CLOCAL | CREAD;
    tio.c_iflag = IGNPAR;
    tio.c_oflag = 0;
    tio.c_lflag = 0;

    tcflush(m_fd, TCIFLUSH);
    tcsetattr(m_fd, TCSANOW, &tio);

    m_notifier = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
    connect(m_notifier, &QSocketNotifier::activated,
            this, &UartDevice::onReadyRead);

    return true;
}

void UartDevice::writeBytes(const QByteArray& data) {
    //if (m_fd >= 0) ::write(m_fd, data.constData(), data.size());
    ssize_t ret = ::write(m_fd, data.constData(), data.size());
    Q_UNUSED(ret);

}

void UartDevice::onReadyRead() {
    char buf[256];
    int n = ::read(m_fd, buf, sizeof(buf));
    if (n > 0)
        emit bytesReceived(QByteArray(buf, n));
}

