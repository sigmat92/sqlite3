#include "../controller/settingscontroller.h"
#include "../view/settingsview.h"
#include "../service/systemsettingsservice.h"


SettingsController::SettingsController(
        SettingsView *view,
        SystemSettingsService *service,
        AdminAuthService *authService,
        QObject *parent)
    : QObject(parent),
      m_view(view),
      m_service(service),
      m_authService(authService)
{
    connect(m_view, &SettingsView::saveRequested,
            this, &SettingsController::handleSave);

    connect(m_view, &SettingsView::exitRequested,
            this, &SettingsController::handleExit);

    connect(m_view, &SettingsView::dhcpToggled,
            this, &SettingsController::handleDhcpToggle);
}

void SettingsController::handleSave()
{
    m_view->lockControls();

    m_service->setWifi(
        m_view->ssid(),
        m_view->securityKey());

    m_service->setServer(
        m_view->serverIp(),
        m_view->serverPort());

    m_service->setDeviceNetwork(
        m_view->deviceIp(),
        m_view->subnetMask(),
        m_view->gateway());

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
    m_service->setDhcpEnabled(enabled);
}

