#include "rotaryhandler.h"
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>

RotaryHandler::RotaryHandler(const QString &rotaryDevice, const QString &switchDevice, QObject *parent)
    : QObject(parent),
      rotaryDevicePath(rotaryDevice),
      switchDevicePath(switchDevice)
{}

void RotaryHandler::processEvents()
{
    int fdRot = open(rotaryDevicePath.toStdString().c_str(), O_RDONLY);
    int fdSw = open(switchDevicePath.toStdString().c_str(), O_RDONLY);

    if (fdRot < 0 || fdSw < 0) {
        qWarning() << "Failed to open devices";
        return;
    }

    struct input_event ev;
    fd_set readfds;
    int maxfd = qMax(fdRot, fdSw) + 1;

    while (true) {
        FD_ZERO(&readfds);
        FD_SET(fdRot, &readfds);
        FD_SET(fdSw, &readfds);

        int ret = select(maxfd, &readfds, nullptr, nullptr, nullptr);
        if (ret > 0) {
            if (FD_ISSET(fdRot, &readfds)) {
                ssize_t n = read(fdRot, &ev, sizeof(ev));
                if (n == sizeof(ev) && ev.type == EV_REL && ev.code == REL_X) {
                    emit rotated(ev.value);
                }
            }
            if (FD_ISSET(fdSw, &readfds)) {
                ssize_t n = read(fdSw, &ev, sizeof(ev));
                if (n == sizeof(ev) && ev.type == EV_KEY && ev.code == KEY_ENTER) {
                    emit switchChanged(ev.value);
                }
            }
        }
    }

    close(fdRot);
    close(fdSw);
}

