#include "settingscontroller.h"
#include "../view/settingsview.h"
#include "../service/systemsettingsservice.h"
#include "../service/adminauthservice.h"

SettingsController::SettingsController(SettingsView* view,
                                       SystemSettingsService* service,
                                       AdminAuthService* auth,
                                       QObject* parent)
    : QObject(parent),
      m_view(view),
      m_service(service),
      m_auth(auth)
{
    // 🔐 Admin login
    connect(m_view, &SettingsView::adminLoginRequested,
            this, [=](QString pin)
    {
        if (m_auth->authenticate(pin))
            m_view->unlockControls();
        else
            m_view->lockControls();
    });

    // 📡 WiFi connect
    connect(m_view, &SettingsView::wifiConnectRequested,
            m_service, &SystemSettingsService::connectWifi);

    // 🔁 DHCP toggle
    connect(m_view, &SettingsView::dhcpToggled,
            m_service, &SystemSettingsService::enableDHCP);

    // 🌐 Static IP
    connect(m_view, &SettingsView::staticIPRequested,
            m_service, &SystemSettingsService::setStaticIP);
}