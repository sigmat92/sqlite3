#include "rotaryhandler.h"
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>

RotaryHandler::RotaryHandler(const QString &rotaryDevice,
                             const QString &switchDevice,
                             QObject *parent)
    : QObject(parent),
      rotaryDevicePath(rotaryDevice),
      switchDevicePath(switchDevice)
{}

void RotaryHandler::stop()
{
    m_running = false;
}
void RotaryHandler::processEvents()
{

    //Rotary encoder device
    int fdRot = open(rotaryDevicePath.toStdString().c_str(),
                     O_RDONLY | O_NONBLOCK);

    int fdSw = open(switchDevicePath.toStdString().c_str(),
                    O_RDONLY | O_NONBLOCK);

    if (fdRot < 0 || fdSw < 0)
    {
        qWarning() << "Cannot open rotary encoder";
        return;
    }

    input_event ev;
//
    if (ev.type == EV_REL &&
    ev.code == REL_DIAL)
    {
        if (ev.value > 0)
        {
            qDebug() << "Rotary Right";
            emit rotatedRight();
        }
        else
        {
            qDebug() << "Rotary Left";
            emit rotatedLeft();
        }
    }

    if (ev.type == EV_KEY &&
    ev.code == KEY_ENTER &&
    ev.value == 1)
    {
        qDebug() << "Rotary Press";
        emit pressed();
    }
//
    fd_set readfds;

    int maxfd = qMax(fdRot, fdSw) + 1;

    while (m_running)
    {
        FD_ZERO(&readfds);

        FD_SET(fdRot, &readfds);
        FD_SET(fdSw, &readfds);

        timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 200000;

        int ret = select(maxfd,
                         &readfds,
                         nullptr,
                         nullptr,
                         &timeout);

        if (ret <= 0)
            continue;

        if (FD_ISSET(fdRot, &readfds))
{
    while (read(fdRot, &ev, sizeof(ev)) == sizeof(ev))
    {
        if (ev.type == EV_REL &&
            ev.code == REL_X)
        {
            if (ev.value > 0)
            {
                qDebug() << "Rotary Right";
                emit rotatedRight();
            }
            else if (ev.value < 0)
            {
                qDebug() << "Rotary Left";
                emit rotatedLeft();
            }
        }
    }
}
        /*
        if (FD_ISSET(fdRot, &readfds))
        {
            while (read(fdRot, &ev, sizeof(ev)) == sizeof(ev))
            {
                    qDebug() << "ROT:"
                 << "type=" << ev.type
                 << "code=" << ev.code
                 << "value=" << ev.value;

                if (ev.type == EV_REL &&
                    ev.code == REL_DIAL)
                {
                    if (ev.value > 0)
                        emit rotatedRight();
                    else
                        emit rotatedLeft();
                }
            }
        }
        */
        if (FD_ISSET(fdSw, &readfds))
        {
            while (read(fdSw, &ev, sizeof(ev)) == sizeof(ev))
            {
                if (ev.type == EV_KEY &&
                    ev.code == KEY_ENTER &&
                    ev.value == 1)
                {
                    emit pressed();
                }
            }
        }
    }

    close(fdRot);
    close(fdSw);
}
/*
void RotaryHandler::processEvents()
{
    int fdRot = open(rotaryDevicePath.toStdString().c_str(), O_RDONLY | O_NONBLOCK);
    int fdSw  = open(switchDevicePath.toStdString().c_str(), O_RDONLY | O_NONBLOCK);

    if (fdRot < 0 || fdSw < 0) {
        qWarning() << "Failed to open rotary devices";
        return;
    }

    input_event ev;
    fd_set readfds;
    int maxfd = qMax(fdRot, fdSw) + 1;

    while (m_running) {
        FD_ZERO(&readfds);
        FD_SET(fdRot, &readfds);
        FD_SET(fdSw, &readfds);

        int ret = select(maxfd, &readfds, nullptr, nullptr, nullptr);
        if (ret <= 0) continue;

        //ROTATION 
        if (FD_ISSET(fdRot, &readfds)) {
            if (read(fdRot, &ev, sizeof(ev)) == sizeof(ev)) {
                if (ev.type == EV_REL && ev.code == REL_DIAL) {
                    if (ev.value > 0)
                        emit rotatedRight();
                    else
                        emit rotatedLeft();
                }
            }
        }

        // PRESS 
        if (FD_ISSET(fdSw, &readfds)) {
            if (read(fdSw, &ev, sizeof(ev)) == sizeof(ev)) {
                if (ev.type == EV_KEY &&
                    ev.code == KEY_ENTER &&
                    ev.value == 1) {
                    emit pressed();
                }
            }
        }
    }

    close(fdRot);
    close(fdSw);
}
*/