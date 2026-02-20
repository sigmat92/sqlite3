#pragma once
#include <QObject>
#include "model/settingsmodel.h"
#include "storage/settingsrepository.h"

class SettingsService : public QObject
{
    Q_OBJECT
public:
    SettingsService(SettingsModel* m,
                    SettingsRepository* r,
                    QObject* parent=nullptr);
    SettingsModel* getModel() const;

public slots:
    void save();
    void load();
    void scanWifi();
    void testConnection();
    void applyNetwork();

signals:
    void wifiListReady(QStringList);
    void connectivityResult(bool);

private:
    SettingsModel* model;
    SettingsRepository* repo;
};

