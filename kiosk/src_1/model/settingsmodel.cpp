#include "settingsmodel.h"

SettingsModel::SettingsModel(QObject* parent)
    : QObject(parent)
{
}

// SSID
QString SettingsModel::ssid() const
{
    return m_ssid;
}

void SettingsModel::setSsid(const QString& value)
{
    if (m_ssid == value) return;
    m_ssid = value;
    emit ssidChanged();
}

// Password
QString SettingsModel::password() const
{
    return m_password;
}

void SettingsModel::setPassword(const QString& value)
{
    if (m_password == value) return;
    m_password = value;
    emit passwordChanged();
}

// DHCP
bool SettingsModel::dhcpEnabled() const
{
    return m_dhcpEnabled;
}

void SettingsModel::setDhcpEnabled(bool value)
{
    if (m_dhcpEnabled == value) return;
    m_dhcpEnabled = value;
    emit dhcpEnabledChanged();
}
