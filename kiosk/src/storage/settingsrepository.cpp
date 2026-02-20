#include "settingsrepository.h"
#include "model/settingsmodel.h"
#include <QSettings>

SettingsRepository::SettingsRepository(QObject* parent)
    : QObject(parent)
{
}

void SettingsRepository::save(SettingsModel* model)
{
    QSettings s("CareNest", "Kiosk");

    s.setValue("ssid", model->ssid());
    s.setValue("password", model->password());
}

void SettingsRepository::load(SettingsModel* model)
{
    QSettings s("CareNest", "Kiosk");

    model->setSsid(s.value("ssid").toString());
    model->setPassword(s.value("password").toString());
}
