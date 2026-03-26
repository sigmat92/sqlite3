#include "settingsauthservice.h"

SettingsAuthService::SettingsAuthService(QObject* parent)
    : QObject(parent)
{}

bool SettingsAuthService::authenticate(const QString& password)
{
    return password == "admin123";   // Change to SHA256 later
}

