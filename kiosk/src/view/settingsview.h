#pragma once

#include "baseview.h"
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QTabWidget>

class SettingsView : public BaseView
{
    Q_OBJECT

public:
    explicit SettingsView(QWidget *parent = nullptr);

    // ===== Lock / Unlock (Controller uses this) =====
    void lockControls();
    void unlockControls();

    // ===== WIFI =====
    QString ssid() const;
    QString securityType() const;
    QString securityKey() const;
    int deviceId() const;

    // ===== SERVER =====
    QString serverIp() const;
    int serverPort() const;

    // ===== DEVICE =====
    QString deviceIp() const;
    QString subnetMask() const;
    QString gateway() const;

    bool isDhcpEnabled() const;
    bool isAutoSendEnabled() const;
    QString usbMode() const;

signals:
    void saveRequested();
    void exitRequested();
    void dhcpToggled(bool);

private:
    void setupUi();
    QWidget* createIpFieldRow(QLineEdit* fields[4]);

    // Tabs
    QTabWidget *m_tabs;
    QWidget *m_dateTab;
    QWidget *m_calibrationTab;
    QWidget *m_commTab;

    // WIFI
    QLineEdit *m_ssid;
    QComboBox *m_securityType;
    QLineEdit *m_securityKey;
    QLineEdit *m_deviceId;

    // SERVER
    QLineEdit *m_serverIp[4];
    QLineEdit *m_serverPort;

    // DEVICE
    QLineEdit *m_deviceIp[4];
    QLineEdit *m_subnet[4];
    QLineEdit *m_gateway[4];

    // Bottom Controls
    QPushButton *m_dhcpBtn;
    QCheckBox *m_autoSend;
    QRadioButton *m_usbDevice;
    QRadioButton *m_usbHostMSC;
    QRadioButton *m_usbHostCDC;
    QButtonGroup *m_usbGroup;

    QPushButton *m_saveBtn;
    QPushButton *m_exitBtn;

    bool m_dhcpEnabled = false;
};