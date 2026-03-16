#pragma once
#include <QObject>

class SettingsView;
class SystemSettingsService;
class AdminAuthService;

class SettingsController : public QObject
{
    Q_OBJECT
public:
    explicit SettingsController(SettingsView *view,
                                SystemSettingsService *service,
                                AdminAuthService *authService,
                                QObject *parent = nullptr);

signals:
    void exitToHomeRequested();
    
private slots:
    void handleSave();
    void handleExit();
    void handleDhcpToggle(bool enabled);

private:
    SettingsView *m_view;
    SystemSettingsService *m_service;
    AdminAuthService *m_authService;
};