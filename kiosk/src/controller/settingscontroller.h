#pragma once
#include <QObject>
#include "view/settingsview.h"
#include "service/settingsservice.h"

class SettingsController : public QObject
{
    Q_OBJECT
public:
    SettingsController(SettingsView* v,
                       SettingsService* s,
                       SettingsModel* m,
                       QObject* parent=nullptr);
};

