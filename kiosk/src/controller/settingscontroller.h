#pragma once
#include <QObject>

class SettingsView;
class SystemSettingsService;
class AdminAuthService;

class SettingsController : public QObject
{
    Q_OBJECT
public:
    explicit SettingsController(SettingsView* view,
                                SystemSettingsService* service,
                                AdminAuthService* auth,
                                QObject* parent = nullptr);

private:
    SettingsView* m_view;
    SystemSettingsService* m_service;
    AdminAuthService* m_auth;
};