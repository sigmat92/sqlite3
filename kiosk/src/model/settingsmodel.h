#pragma once
#include <QObject>

class SettingsModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString ssid READ ssid WRITE setSsid NOTIFY ssidChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(bool dhcpEnabled READ dhcpEnabled WRITE setDhcpEnabled NOTIFY dhcpEnabledChanged)

public:
    explicit SettingsModel(QObject* parent = nullptr);

    // SSID
    QString ssid() const;
    void setSsid(const QString& value);

    // Password
    QString password() const;
    void setPassword(const QString& value);

    // DHCP
    bool dhcpEnabled() const;
    void setDhcpEnabled(bool value);

signals:
    void ssidChanged();
    void passwordChanged();
    void dhcpEnabledChanged();

private:
    QString m_ssid;
    QString m_password;
    bool m_dhcpEnabled = true;
};
