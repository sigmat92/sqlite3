#pragma once
#include <QObject>

class SystemSettingsService : public QObject
{
    Q_OBJECT
public:
    explicit SystemSettingsService(QObject* parent = nullptr);

public slots:
    void connectWifi(QString ssid, QString password);
    void enableDHCP(bool enable);
    void setStaticIP(QString ip, QString mask, QString gateway);
};