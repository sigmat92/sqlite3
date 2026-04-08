#include "../controller/settingscontroller.h"
#include "../view/settingsview.h"
#include "../service/systemsettingsservice.h"
#include "../service/adminauthservice.h"
#include "service/settingsservice.h"
#include "../storage/settingsrepository.h"
#include <QApplication>
#include <QDebug>


SettingsController::SettingsController(
        SettingsView *view,
        SettingsService *settingsService,
        SettingsRepository *settingsRepo,
        //AdminAuthService *authService,
        QObject *parent)
    : QObject(parent),
      m_view(view),
      m_service(settingsService),
      m_settingsRepo(settingsRepo)
    
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

