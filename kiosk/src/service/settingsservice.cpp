#include "settingsservice.h"
#include <QProcess>
#include "model/settingsmodel.h"
#include <QDebug>

SettingsService::SettingsService(SettingsModel* m,
                                 SettingsRepository* r,
                                 QObject* parent)
    : QObject(parent), model(m), repo(r)
{
}

void SettingsService::save()
{
    repo->save(model);
    applyNetwork();
}

void SettingsService::load()
{
    repo->load(model);
}

void SettingsService::scanWifi()
{
    QProcess proc;
    proc.start("iw wlan0 scan | grep SSID");
    proc.waitForFinished();

    QString out = proc.readAllStandardOutput();
    QStringList lines = out.split("\n");

    QStringList list;
    for(QString l : lines)
        if(l.contains("SSID:"))
            list << l.section("SSID:",1).trimmed();

    emit wifiListReady(list);
}

void SettingsService::testConnection()
{
    QProcess proc;
    proc.start("ping -c 1 8.8.8.8");
    proc.waitForFinished();

    emit connectivityResult(proc.exitCode()==0);
}

//void SettingsService::applyNetwork()
//{
//    if(model->dhcpEnabled)
//        QProcess::execute("udhcpc -i wlan0");
//}

void SettingsService::applyNetwork()
{
    if (!model)
        return;

    if (model->dhcpEnabled())
    {
        qDebug() << "Applying DHCP configuration...";
    }
    else
    {
        qDebug() << "Applying static IP configuration...";
    }
}

SettingsModel* SettingsService::getModel() const
{
    return model;
}
