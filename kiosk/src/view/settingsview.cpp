#include "settingsview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QIntValidator>
#include <QApplication>//dark mode
#include <QDebug>

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
    row->setObjectName("ipFieldRow");
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
    main->setObjectName("contentLayout");
    main->setContentsMargins(20,20,20,20);

    // ================= Tabs =================
    m_tabs = new QTabWidget;
    m_tabs->setObjectName("settingsTabs");
    m_tabs->setTabPosition(QTabWidget::North);
    //m_tabs->setDocumentMode(true);

    m_dateTab = new QWidget;
    m_dateTab->setObjectName("dateTab");
    m_calibrationTab = new QWidget;
    m_calibrationTab->setObjectName("calibrationTab");
    m_commTab = new QWidget;
    m_commTab->setObjectName("commTab");
    m_darkModeTab = new QWidget;
    m_darkModeTab->setObjectName("darkModeTab");

    m_tabs->addTab(m_dateTab, "Date & Time Settings");
    m_tabs->addTab(m_calibrationTab, "Calibration Settings");
    m_tabs->addTab(m_commTab, "Comm. Settings");
    m_tabs->addTab(m_darkModeTab, "Dark Mode Settings");

    main->addWidget(m_tabs);

    // ================= DATE TAB =================
    QVBoxLayout *dateLayout = new QVBoxLayout(m_dateTab);
    dateLayout->setObjectName("dateLayout");

    QLabel *dateLabel = new QLabel("System Date & Time");
    dateLabel->setObjectName("dateLabel");
    //dateLabel->setStyleSheet("font-weight:bold; font-size:18px;");

    dateLayout->addWidget(dateLabel);
    dateLayout->addSpacing(20);
    dateLayout->addWidget(new QPushButton("Set Date"));
    dateLayout->addWidget(new QPushButton("Set Time"));
    //dateLayout->addWidget(new QPushButton("Sync with Server"));
    dateLayout->addStretch();

    // -------- Save / Exit from DATE TAB--------
    
    m_saveBtn = new QPushButton("Save");
    m_saveBtn->setObjectName("saveBtn");
    m_exitBtn = new QPushButton("Exit");
    m_exitBtn->setObjectName("exitBtn");

    dateLayout->addWidget(m_saveBtn);
    dateLayout->addWidget(m_exitBtn);

    connect(m_saveBtn,&QPushButton::clicked,this,&SettingsView::saveRequested);
    connect(m_exitBtn,&QPushButton::clicked,this,&SettingsView::exitRequested);

    // ================= CALIBRATION TAB =================

    QVBoxLayout *calLayout = new QVBoxLayout(m_calibrationTab);
    calLayout->setObjectName("calLayout");
    QLabel *calLabel = new QLabel("Device Calibration");
    calLabel->setObjectName("calLabel");
    //calLabel->setStyleSheet("font-weight:bold; font-size:18px;");

    calLayout->addWidget(calLabel);
    calLayout->addSpacing(20);
    calLayout->addWidget(new QPushButton("Start Calibration"));
    calLayout->addWidget(new QPushButton("Reset Calibration"));
    calLayout->addStretch();

    // -------- Save / Exit from CALIBRATION TAB--------
    
    m_saveBtn = new QPushButton("Save");
    m_saveBtn->setObjectName("saveBtn");
    m_exitBtn = new QPushButton("Exit");
    m_exitBtn->setObjectName("exitBtn");

    calLayout->addWidget(m_saveBtn);
    calLayout->addWidget(m_exitBtn);

    //calLayout->addLayout(darkModeBtnLayout);
    connect(m_saveBtn,&QPushButton::clicked,this,&SettingsView::saveRequested);
    connect(m_exitBtn,&QPushButton::clicked,this,&SettingsView::exitRequested);

    // ================= COMM TAB =================
    QVBoxLayout *commLayout = new QVBoxLayout(m_commTab);
    commLayout->setObjectName("commLayout");
    commLayout->setContentsMargins(40,30,40,30);
    commLayout->setSpacing(20);

    // ================= DARK MODE TAB =================
    QVBoxLayout *darkModeLayout = new QVBoxLayout(m_darkModeTab);
    darkModeLayout->setObjectName("darkModeLayout");
    darkModeLayout->setContentsMargins(40,30,40,30);
    darkModeLayout->setSpacing(20);
    // Dark Mode Toggle
    //1
        QPushButton *modeBtn = new QPushButton("Toggle Dark Mode");
        modeBtn->setObjectName("modeBtn");
    /*
        modeBtn->setStyleSheet(
            "font-size:24px;"
            "font-weight:bold;"
            "background:#0d47a1;"
            "color:white;"
            "border-radius:8px;"
        );
    */
        darkModeLayout->addWidget(modeBtn);

        connect(modeBtn, &QPushButton::clicked, this, [this]() {
            //qDebug() << "modeBtn clicked from settingsview for toggling theme Dark:";
            static bool dark = false;
            dark = !dark;
            //qDebug() << "Emitting themeChanged signal from view with dark bool : " << dark;
            emit themeChanged(dark);
        });

        

    // -------- Save / Exit from DARK MODE TAB--------
    QHBoxLayout *darkModeBtnLayout = new QHBoxLayout;
    darkModeBtnLayout->setObjectName("darkModeBtnLayout");
    m_saveBtn = new QPushButton("Save");
    m_saveBtn->setObjectName("saveBtn");
    m_exitBtn = new QPushButton("Exit");
    m_exitBtn->setObjectName("exitBtn");

    darkModeBtnLayout->addWidget(m_saveBtn);
    darkModeBtnLayout->addWidget(m_exitBtn);

    darkModeLayout->addLayout(darkModeBtnLayout);
    connect(m_saveBtn,&QPushButton::clicked,this,&SettingsView::saveRequested);
    connect(m_exitBtn,&QPushButton::clicked,this,&SettingsView::exitRequested);
    
    //network tab
        
    // -------- WIFI --------
    QLabel *wifiLabel = new QLabel("WIFI SETTINGS");
    wifiLabel->setObjectName("wifiLabel");
    //wifiLabel->setStyleSheet("font-weight:bold;");

    QGridLayout *wifiGrid = new QGridLayout;
    wifiGrid->setObjectName("wifiGrid");
    m_ssid = new QLineEdit;
    m_ssid->setObjectName("ssid");
    m_securityType = new QComboBox;
    m_securityType->setObjectName("securityType");

    m_securityType->addItems({"WPA/WPA2","WPA2","Open"});
    m_securityType->setObjectName("securityType");
    m_securityKey = new QLineEdit;
    m_securityKey->setObjectName("securityKey");
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
    serverLabel->setObjectName("serverLabel");
    //serverLabel->setStyleSheet("font-weight:bold;");
    commLayout->addWidget(serverLabel);

    QGridLayout *serverGrid = new QGridLayout;
    serverGrid->setObjectName("serverGrid");

    serverGrid->addWidget(new QLabel("IP ADDRESS:"),0,0);
    serverGrid->addWidget(createIpFieldRow(m_serverIp),0,1);

    m_serverPort = new QLineEdit;
    serverGrid->addWidget(new QLabel("PORT NO:"),1,0);
    serverGrid->addWidget(m_serverPort,1,1);

    commLayout->addLayout(serverGrid);

    // -------- DEVICE --------
    QLabel *deviceLabel = new QLabel("Device Settings");
    deviceLabel->setObjectName("deviceLabel");
    //deviceLabel->setStyleSheet("font-weight:bold;");
    commLayout->addWidget(deviceLabel);

    QGridLayout *deviceGrid = new QGridLayout;
    deviceGrid->setObjectName("deviceGrid");
    deviceGrid->addWidget(new QLabel("IP ADDRESS:"),0,0);
    deviceGrid->addWidget(createIpFieldRow(m_deviceIp),0,1);

    deviceGrid->addWidget(new QLabel("SUBNET MASK:"),1,0);
    deviceGrid->addWidget(createIpFieldRow(m_subnet),1,1);

    deviceGrid->addWidget(new QLabel("DEF. GATEWAY:"),2,0);
    deviceGrid->addWidget(createIpFieldRow(m_gateway),2,1);

    commLayout->addLayout(deviceGrid);

    // -------- Bottom Controls --------
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->setObjectName("bottomLayout");
    m_dhcpBtn = new QPushButton("Enable DHCP");
    m_dhcpBtn->setObjectName("dhcpBtn");
    m_autoSend = new QCheckBox("Auto Send");
    m_autoSend->setObjectName("autoSend");

    m_usbDevice = new QRadioButton("USB Device");
    m_usbDevice->setObjectName("usbDevice");
    m_usbHostMSC = new QRadioButton("USB Host MSC");
    m_usbHostMSC->setObjectName("usbHostMSC");
    m_usbHostCDC = new QRadioButton("USB Host CDC");
    m_usbHostCDC->setObjectName("usbHostCDC");

    m_usbGroup = new QButtonGroup(this);
    m_usbGroup->setObjectName("usbGroup");
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
    btnLayout->setObjectName("btnLayout");
    m_saveBtn = new QPushButton("Save");
    m_saveBtn->setObjectName("saveBtn");
    m_exitBtn = new QPushButton("Exit");
    m_exitBtn->setObjectName("exitBtn");

    //postBtn = new QPushButton("Post Vitals", this);
    //postBtn->setObjectName("postBtn");

    //btnLayout->addWidget(postBtn);
    btnLayout->addWidget(m_saveBtn);
    btnLayout->addWidget(m_exitBtn);
        
    commLayout->addLayout(btnLayout);

    // -------- Connections --------
    connect(m_saveBtn,&QPushButton::clicked,this,&SettingsView::saveRequested);
    connect(m_exitBtn,&QPushButton::clicked,this,&SettingsView::exitRequested);
  
    //connect(postBtn, &QPushButton::clicked, this, [this]() {

    //    qDebug() << "postBtn clicked from settingsview for posting vitals to server:";
    //    emit postVitals();
    //    qDebug() << "Emitting postVitals signal from settingsview";
            
    //    });

    connect(m_dhcpBtn,&QPushButton::clicked,this,[this](){
        m_dhcpEnabled = !m_dhcpEnabled;
        emit dhcpToggled(m_dhcpEnabled);
    });
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
