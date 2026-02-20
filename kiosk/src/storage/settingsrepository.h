#pragma once

#include <QObject>

class SettingsModel;

class SettingsRepository : public QObject
{
    Q_OBJECT

public:
    explicit SettingsRepository(QObject* parent = nullptr);

    void save(SettingsModel* model);
    void load(SettingsModel* model);
};
