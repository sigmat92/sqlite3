#pragma once
#include <QString>

class SystemSettingsService
{
public:
    void setWifi(const QString &ssid, const QString &key);
    void setServer(const QString &ip, int port);
    void setDeviceNetwork(const QString &ip,
                          const QString &subnet,
                          const QString &gateway);
    void setDhcpEnabled(bool enabled);

    void save();
};