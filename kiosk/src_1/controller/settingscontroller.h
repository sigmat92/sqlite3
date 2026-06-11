#pragma once
#include <QObject>

//class SettingsView;
//class SettingsService;
//class SettingsRepository;
//class AdminAuthService;

class SettingsView;
class SettingsService;
class SettingsRepository;
class VitalsService;
class SyncService;

class SettingsController : public QObject
{
    Q_OBJECT

public:
    explicit SettingsController(
        SettingsView *view,
        SettingsService *settingsService,
        SettingsRepository *settingsRepo,
        VitalsService *vitalsService,
        SyncService *syncService,
        QObject *parent = nullptr
    );
    /*
    explicit SettingsController(
        SettingsView *view,
        //ystemSettingsService *service,
        SettingsService *settingsService,
        SettingsRepository *settingsRepo,
        //AdminAuthService *authService,
        QObject *parent);
    */
signals:
    void exitToHomeRequested();
    void settingsRequested();
    
private slots:

    void onPostVitals();
    void handleSave();
    void handleExit();
    void handleDhcpToggle(bool enabled);

private:
    //ttingsView *m_view;
    //ttingsService *m_service;
    //ttingsRepository *m_settingsRepo;
    //minAuthService *m_authService;

    SettingsView *m_view;
    SettingsService *m_service;
    SettingsRepository *m_settingsRepo;

    // NEW dependencies
    VitalsService *m_vitalsService;
    SyncService *m_syncService;
};