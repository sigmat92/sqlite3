#include "systemsettingsservice.h"
#include <QProcess>
#include <QDebug>

SystemSettingsService::SystemSettingsService(QObject* parent)
    : QObject(parent)
{
}

void SystemSettingsService::connectWifi(QString ssid, QString password)
{
    QString cmd = QString("nmcli dev wifi connect \"%1\" password \"%2\"")
                  .arg(ssid)
                  .arg(password);

    QProcess::execute(cmd);
}

void SystemSettingsService::enableDHCP(bool enable)
{
    if (enable)
        QProcess::execute("nmcli connection modify wlan0 ipv4.method auto");
}

void SystemSettingsService::setStaticIP(QString ip,
                                        QString mask,
                                        QString gateway)
{
    QString cmd1 = QString("nmcli connection modify wlan0 ipv4.method manual ipv4.addresses %1/%2")
                   .arg(ip)
                   .arg(mask);

    QString cmd2 = QString("nmcli connection modify wlan0 ipv4.gateway %1")
                   .arg(gateway);

    QProcess::execute(cmd1);
    QProcess::execute(cmd2);
}