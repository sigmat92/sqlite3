#pragma once
#include <QObject>

class SettingsAuthService : public QObject
{
    Q_OBJECT
public:
    explicit SettingsAuthService(QObject* parent=nullptr);
    bool authenticate(const QString& password);
};

