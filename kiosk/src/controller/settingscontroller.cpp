#include "../controller/settingscontroller.h"
#include "../view/settingsview.h"
#include "../service/systemsettingsservice.h"
#include "../service/adminauthservice.h"
#include "service/settingsservice.h"
#include "../storage/settingsrepository.h"
#include "service/vitalsservice.h"
#include "service/syncservice.h"
#include <QApplication>
#include <QDebug>

SettingsController::SettingsController(
        SettingsView *view,
        SettingsService *settingsService,
        SettingsRepository *settingsRepo,
        VitalsService *vitalsService,
        SyncService *syncService,
        QObject *parent)
    : QObject(parent),
      m_view(view),
      m_service(settingsService),
      m_settingsRepo(settingsRepo),   
      m_vitalsService(vitalsService),
      m_syncService(syncService)

{
    connect(m_view, &SettingsView::saveRequested,
            this, &SettingsController::handleSave);

    connect(m_view, &SettingsView::exitRequested,
            this, &SettingsController::handleExit);

    connect(m_view, &SettingsView::dhcpToggled,
            this, &SettingsController::handleDhcpToggle);
    //dark mode
 
    connect(m_view, &SettingsView::themeChanged,
        this, [this](bool dark) {

            qDebug() << "Theme toggle clicked received in controller. Dark:" << dark;

            // 1. Save in DB
            m_settingsRepo->set("theme", dark ? "dark" : "light");

            // 2. Apply instantly
            m_service->applyTheme(dark);
        });

    // Connect post vitals button signal to controller slot
    connect(m_view, &SettingsView::postVitals,
            this, &SettingsController::onPostVitals);


    connect(m_view, &SettingsView::postVitals,
        this, [this]() {
            qDebug() << "postVitals signal received in controller from view";
            // Here you would call the service method to post vitals
            // For example: m_service->postVitals();
            
             qDebug() << "Calling postVitals in service (not implemented)";
             // Simulate posting vitals
             //m_service->postVitals();
             qDebug() << "Vitals posted successfully...";
        });

    //connect(homeView, &HomeView::settingsRequested,
    //             [=]() {
    //                qDebug() << "Settings requested signal received in settings controller, emitting settingsRequested signal to main.cpp";
    //                 //nav->goTo(Screen::Settings);
    //                 emit settingsRequested();
    //             });


}

void SettingsController::onPostVitals()
{
    if (!m_vitalsService) return;

    //QJsonObject currentVitals = m_vitalsService->currentVitals();

    // Optional validation
    // if (!vitals.isValid()) return;

    //syncService->sendVitals(currentVitals);
    qDebug() << "onPostVitals called in controller. SyncService should send vitals now.";
}

void SettingsController::handleSave()
{
    m_view->lockControls();

    //m_service->setWifi(
    //    m_view->ssid(),
    //    m_view->securityKey());

    //m_service->setServer(
    //    m_view->serverIp(),
    //    m_view->serverPort());

    //m_service->setDeviceNetwork(
    //    m_view->deviceIp(),
    //    m_view->subnetMask(),
    //    m_view->gateway());

    m_service->save();

    m_view->unlockControls();
}

void SettingsController::handleExit()
{
    //emit m_view->exitRequested();//wrong
    emit exitToHomeRequested();
}

void SettingsController::handleDhcpToggle(bool enabled)
{
    //m_service->setDhcpEnabled(enabled);
}

