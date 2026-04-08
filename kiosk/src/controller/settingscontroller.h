#pragma once
#include <QObject>

class SettingsView;
class SettingsService;
class SettingsRepository;
class AdminAuthService;

class SettingsController : public QObject
{
    Q_OBJECT
public:
    /*
    explicit SettingsController(SettingsView *view,
                                SystemSettingsService *service,
                                AdminAuthService *authService,
                                QObject *parent = nullptr);
    */
    explicit SettingsController(
        SettingsView *view,
        /*SystemSettingsService *service,*/
        SettingsService *settingsService,
        SettingsRepository *settingsRepo,
        //AdminAuthService *authService,
        QObject *parent);

signals:
    void exitToHomeRequested();
    
private slots:
    void handleSave();
    void handleExit();
    void handleDhcpToggle(bool enabled);

private:
    SettingsView *m_view;
    SettingsService *m_service;
    SettingsRepository *m_settingsRepo;
    AdminAuthService *m_authService;
};