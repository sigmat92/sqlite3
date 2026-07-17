#include "gpiokeyhandler.h"

#include <QDebug>
#include <QThread>
#include <QProcess>

GPIOKeyHandler::GPIOKeyHandler(QObject *parent)
    : QObject(parent)
{
}

void GPIOKeyHandler::stop()
{
    m_running = false;
}

bool GPIOKeyHandler::readGPIO(int gpio)
{
    QProcess proc;

    proc.start("/usr/bin/gpioget",
               QStringList()
                   << "--chip"
                   << "gpiochip0"
                   << QString::number(gpio));

    // Wait for process to start
    if (!proc.waitForStarted(100))
    {
        qDebug() << "Failed to start gpioget";
        return false;
    }

    // Wait until it exits
    if (!proc.waitForFinished(1000))
    {
        qDebug() << "gpioget timeout";
        proc.kill();
        proc.waitForFinished();
        return false;
    }

    QString out = QString::fromUtf8(proc.readAllStandardOutput()).trimmed();
    QString err = QString::fromUtf8(proc.readAllStandardError()).trimmed();

    if (!err.isEmpty())
        qDebug() << "gpioget stderr:" << err;

    //qDebug() << "GPIO" << gpio << ":" << out;

    // gpioget v2 outputs "active" or "inactive"
    return out.contains("active") && !out.contains("inactive");
}

/*
bool GPIOKeyHandler::readGPIO(int gpio)
{
    //
    // Temporary implementation.
    //
    // Replace this with libgpiod v2 later.
    //

    //
    //gpio = 02;
    QProcess proc;

    proc.start("/usr/bin/gpioget",
               QStringList()
                   << "--chip"
                   << "gpiochip0"
                   << QString::number(gpio));

                   if (!proc.waitForStarted(1000))
{
    qDebug() << "Failed to start gpioget";
    return false;
}

if (!proc.waitForFinished(1000))
{
    qDebug() << "gpioget timeout";
    proc.kill();
    proc.waitForFinished();
    return false;
}
    QString out = proc.readAllStandardOutput().trimmed();

    bool active = out.endsWith("=active");

    //qDebug()
    //<< out
    //<< "active =" << active;

    return active;

    //proc.waitForFinished(100);

    //QString out = proc.readAllStandardOutput();

    //qDebug() << "GPIO" << gpio << ":" << out;

    //return out.contains("active");
}
*/
void GPIOKeyHandler::processEvents()
{
    qDebug() << "******** GPIO Thread Started ********";

    lastMute   = readGPIO(2);

    lastNibp   = readGPIO(3);
    lastFreeze = readGPIO(4);
    lastPrint  = readGPIO(14);
    lastMenu   = readGPIO(15);

    while (m_running)
    {
        bool state = readGPIO(2);

        //----------------------------
        // MUTE
        //----------------------------
        //qDebug() << "lastMute =" << lastMute
        // << "state =" << state;

        //state = readGPIO(2);

        if (state != lastMute)
        {
            lastMute = state;

            if (state)
            {
                qDebug() << "GPIO : MUTE";
                emit mutePressed();
            }
        }

        //----------------------------
        // NIBP
        //----------------------------

        state = readGPIO(3);

        if (state != lastNibp)
        {
            lastNibp = state;

            if (state)
            {
                qDebug() << "GPIO : NIBP";
                emit nibpPressed();
            }
        }

        //----------------------------
        // FREEZE
        //----------------------------

        state = readGPIO(4);

        if (state != lastFreeze)
        {
            lastFreeze = state;

            if (state)
            {
                qDebug() << "GPIO : FREEZE";
                emit freezePressed();
            }
        }

        //----------------------------
        // PRINT
        //----------------------------

        state = readGPIO(14);

        if (state != lastPrint)
        {
            lastPrint = state;

            if (state)
            {
                qDebug() << "GPIO : PRINT";
                emit printPressed();
            }
        }

        //----------------------------
        // MENU
        //----------------------------

        state = readGPIO(15);

        if (state != lastMenu)
        {
            lastMenu = state;

            if (state)
            {
                qDebug() << "GPIO : MENU";
                emit menuPressed();
            }
        }

        QThread::msleep(20);
    }
}