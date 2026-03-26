#include "settingsview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QIntValidator>

// =========================================
// Constructor
// =========================================
SettingsView::SettingsView(QWidget *parent)
    : BaseView("Settings", parent)
{
    setupUi();
}

// =========================================
// Utility: Create IP Row
// =========================================
QWidget* SettingsView::createIpFieldRow(QLineEdit* fields[4])
{
    QWidget *row = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(row);
    layout->setSpacing(5);

    for(int i = 0; i < 4; i++)
    {
        fields[i] = new QLineEdit;
        fields[i]->setFixedWidth(60);
        fields[i]->setMaxLength(3);
        fields[i]->setValidator(new QIntValidator(0,255,this));
        layout->addWidget(fields[i]);

        if(i < 3)
            layout->addWidget(new QLabel("."));
    }

    return row;
}

// =========================================
// Setup UI
// =========================================
void SettingsView::setupUi()
{
    QVBoxLayout *main = new QVBoxLayout(m_contentWidget);
    main->setContentsMargins(20,20,20,20);

    // ================= Tabs =================
    m_tabs = new QTabWidget;
    m_tabs->setTabPosition(QTabWidget::North);
    m_tabs->setDocumentMode(true);

    m_dateTab = new QWidget;
    m_calibrationTab = new QWidget;
    m_commTab = new QWidget;

    m_tabs->addTab(m_dateTab, "Date & Time Settings");
    m_tabs->addTab(m_calibrationTab, "Calibration Settings");
    m_tabs->addTab(m_commTab, "Comm. Settings");

    main->addWidget(m_tabs);

    // ================= DATE TAB =================
    QVBoxLayout *dateLayout = new QVBoxLayout(m_dateTab);

    QLabel *dateLabel = new QLabel("System Date & Time");
    dateLabel->setStyleSheet("font-weight:bold; font-size:18px;");

    dateLayout->addWidget(dateLabel);
    dateLayout->addSpacing(20);
    dateLayout->addWidget(new QPushButton("Set Date"));
    dateLayout->addWidget(new QPushButton("Set Time"));
    dateLayout->addWidget(new QPushButton("Sync with Server"));
    dateLayout->addStretch();

    // ================= CALIBRATION TAB =================
    QVBoxLayout *calLayout = new QVBoxLayout(m_calibrationTab);

    QLabel *calLabel = new QLabel("Device Calibration");
    calLabel->setStyleSheet("font-weight:bold; font-size:18px;");

    calLayout->addWidget(calLabel);
    calLayout->addSpacing(20);
    calLayout->addWidget(new QPushButton("Start Calibration"));
    calLayout->addWidget(new QPushButton("Reset Calibration"));
    calLayout->addStretch();

    // ================= COMM TAB =================
    QVBoxLayout *commLayout = new QVBoxLayout(m_commTab);
    commLayout->setContentsMargins(40,30,40,30);
    commLayout->setSpacing(20);

    // -------- WIFI --------
    QLabel *wifiLabel = new QLabel("WIFI SETTINGS");
    wifiLabel->setStyleSheet("font-weight:bold;");

    QGridLayout *wifiGrid = new QGridLayout;

    m_ssid = new QLineEdit;
    m_securityType = new QComboBox;
    m_securityType->addItems({"WPA/WPA2","WPA2","Open"});
    m_securityKey = new QLineEdit;
    m_deviceId = new QLineEdit;

    wifiGrid->addWidget(new QLabel("SSID:"),0,0);
    wifiGrid->addWidget(m_ssid,0,1);

    wifiGrid->addWidget(new QLabel("SECURITY TYPE:"),1,0);
    wifiGrid->addWidget(m_securityType,1,1);

    wifiGrid->addWidget(new QLabel("SECURITY KEY:"),2,0);
    wifiGrid->addWidget(m_securityKey,2,1);

    wifiGrid->addWidget(new QLabel("DEVICE ID:"),2,2);
    wifiGrid->addWidget(m_deviceId,2,3);

    commLayout->addWidget(wifiLabel);
    commLayout->addLayout(wifiGrid);

    // -------- SERVER --------
    QLabel *serverLabel = new QLabel("SERVER SETTINGS");
    serverLabel->setStyleSheet("font-weight:bold;");
    commLayout->addWidget(serverLabel);

    QGridLayout *serverGrid = new QGridLayout;

    serverGrid->addWidget(new QLabel("IP ADDRESS:"),0,0);
    serverGrid->addWidget(createIpFieldRow(m_serverIp),0,1);

    m_serverPort = new QLineEdit;
    serverGrid->addWidget(new QLabel("PORT NO:"),1,0);
    serverGrid->addWidget(m_serverPort,1,1);

    commLayout->addLayout(serverGrid);

    // -------- DEVICE --------
    QLabel *deviceLabel = new QLabel("DEVICE SETTINGS");
    deviceLabel->setStyleSheet("font-weight:bold;");
    commLayout->addWidget(deviceLabel);

    QGridLayout *deviceGrid = new QGridLayout;

    deviceGrid->addWidget(new QLabel("IP ADDRESS:"),0,0);
    deviceGrid->addWidget(createIpFieldRow(m_deviceIp),0,1);

    deviceGrid->addWidget(new QLabel("SUBNET MASK:"),1,0);
    deviceGrid->addWidget(createIpFieldRow(m_subnet),1,1);

    deviceGrid->addWidget(new QLabel("DEF. GATEWAY:"),2,0);
    deviceGrid->addWidget(createIpFieldRow(m_gateway),2,1);

    commLayout->addLayout(deviceGrid);

    // -------- Bottom Controls --------
    QHBoxLayout *bottomLayout = new QHBoxLayout;

    m_dhcpBtn = new QPushButton("ENABLE");
    m_autoSend = new QCheckBox("AUTO SEND");

    m_usbDevice = new QRadioButton("USB Device");
    m_usbHostMSC = new QRadioButton("USB Host MSC");
    m_usbHostCDC = new QRadioButton("USB Host CDC");

    m_usbGroup = new QButtonGroup(this);
    m_usbGroup->addButton(m_usbDevice);
    m_usbGroup->addButton(m_usbHostMSC);
    m_usbGroup->addButton(m_usbHostCDC);

    bottomLayout->addWidget(m_dhcpBtn);
    bottomLayout->addWidget(m_autoSend);
    bottomLayout->addWidget(m_usbDevice);
    bottomLayout->addWidget(m_usbHostMSC);
    bottomLayout->addWidget(m_usbHostCDC);

    commLayout->addLayout(bottomLayout);

    // -------- Save / Exit --------
    QHBoxLayout *btnLayout = new QHBoxLayout;

    m_saveBtn = new QPushButton("SAVE");
    m_exitBtn = new QPushButton("EXIT");

    btnLayout->addWidget(m_saveBtn);
    btnLayout->addWidget(m_exitBtn);

    commLayout->addLayout(btnLayout);

    // -------- Connections --------
    connect(m_saveBtn,&QPushButton::clicked,this,&SettingsView::saveRequested);
    connect(m_exitBtn,&QPushButton::clicked,this,&SettingsView::exitRequested);

    connect(m_dhcpBtn,&QPushButton::clicked,this,[this](){
        m_dhcpEnabled = !m_dhcpEnabled;
        emit dhcpToggled(m_dhcpEnabled);
    });

    // -------- Styling --------
    m_tabs->setStyleSheet(R"(
        QTabBar::tab {
            background: #e0e0e0;
            padding: 10px 25px;
            border-radius: 6px;
            font-weight: 500;
        }

        QTabBar::tab:selected {
            background: #4A90E2;
            color: white;
        }

        QTabWidget::pane {
            border: 1px solid #c0c0c0;
            top: -1px;
        }

        QPushButton {
            background-color: #4A90E2;
            color: white;
            padding: 8px;
            border-radius: 6px;
        }

        QPushButton:hover {
            background-color: #357ABD;
        }
    )");
}

// =========================================
// Lock / Unlock
// =========================================
void SettingsView::lockControls()
{
    this->setEnabled(false);
}

void SettingsView::unlockControls()
{
    this->setEnabled(true);
}

// =========================================
// Getters
// =========================================
QString SettingsView::ssid() const { return m_ssid->text(); }
QString SettingsView::securityType() const { return m_securityType->currentText(); }
QString SettingsView::securityKey() const { return m_securityKey->text(); }
int SettingsView::deviceId() const { return m_deviceId->text().toInt(); }

QString SettingsView::serverIp() const
{
    return QString("%1.%2.%3.%4")
            .arg(m_serverIp[0]->text())
            .arg(m_serverIp[1]->text())
            .arg(m_serverIp[2]->text())
            .arg(m_serverIp[3]->text());
}

int SettingsView::serverPort() const
{
    return m_serverPort->text().toInt();
}

QString SettingsView::deviceIp() const
{
    return QString("%1.%2.%3.%4")
            .arg(m_deviceIp[0]->text())
            .arg(m_deviceIp[1]->text())
            .arg(m_deviceIp[2]->text())
            .arg(m_deviceIp[3]->text());
}

QString SettingsView::subnetMask() const
{
    return QString("%1.%2.%3.%4")
            .arg(m_subnet[0]->text())
            .arg(m_subnet[1]->text())
            .arg(m_subnet[2]->text())
            .arg(m_subnet[3]->text());
}

QString SettingsView::gateway() const
{
    return QString("%1.%2.%3.%4")
            .arg(m_gateway[0]->text())
            .arg(m_gateway[1]->text())
            .arg(m_gateway[2]->text())
            .arg(m_gateway[3]->text());
}

bool SettingsView::isDhcpEnabled() const { return m_dhcpEnabled; }
bool SettingsView::isAutoSendEnabled() const { return m_autoSend->isChecked(); }

QString SettingsView::usbMode() const
{
    if(m_usbDevice->isChecked()) return "USB_DEVICE";
    if(m_usbHostMSC->isChecked()) return "USB_HOST_MSC";
    if(m_usbHostCDC->isChecked()) return "USB_HOST_CDC";
    return "";
}