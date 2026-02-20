#include "settingsview.h"
#include "model/settingsmodel.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>

SettingsView::SettingsView(QWidget* parent)
    : QWidget(parent)
{
    
    //setStyleSheet("background-color: #1e1e1e; color: white;");

        setStyleSheet(
        "QWidget { background-color: #1e1e1e; color: white; }"
        "QPushButton { background-color: #0078D7; padding: 10px; border-radius: 6px; }"
        "QPushButton:hover { background-color: #005fa3; }"
        "QComboBox { padding: 8px; }"
        "QLineEdit { padding: 8px; }"
    );

    setWindowTitle("Settings");
    //setStyleSheet("background:#f5f5f5;");

    auto* layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("WiFi SSID"));
    ssidCombo = new QComboBox;
    layout->addWidget(ssidCombo);

    QPushButton* scanBtn = new QPushButton("Scan WiFi");
    layout->addWidget(scanBtn);

    layout->addWidget(new QLabel("Security Key"));
    keyEdit = new QLineEdit;
    keyEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(keyEdit);

    layout->addWidget(new QLabel("Server IP"));
    serverIpEdit = new QLineEdit;
    layout->addWidget(serverIpEdit);

    layout->addWidget(new QLabel("Server Port"));
    portEdit = new QLineEdit;
    layout->addWidget(portEdit);

    layout->addWidget(new QLabel("Device IP"));
    deviceIpEdit = new QLineEdit;
    layout->addWidget(deviceIpEdit);

    layout->addWidget(new QLabel("Subnet"));
    subnetEdit = new QLineEdit;
    layout->addWidget(subnetEdit);

    layout->addWidget(new QLabel("Gateway"));
    gatewayEdit = new QLineEdit;
    layout->addWidget(gatewayEdit);

    dhcpCheck = new QCheckBox("Enable DHCP");
    layout->addWidget(dhcpCheck);

    QPushButton* testBtn = new QPushButton("Test Connectivity");
    layout->addWidget(testBtn);

    QPushButton* saveBtn = new QPushButton("Save");
    layout->addWidget(saveBtn);

    QPushButton* exitBtn = new QPushButton("Exit");
    layout->addWidget(exitBtn);
    //layout->addStretch();
    //layout->setContentsMargins(20, 20, 20, 20);
    //layout->setSpacing(15);
    layout->setAlignment(Qt::AlignTop);
     connect(saveBtn,&QPushButton::clicked,
            this,&SettingsView::saveRequested);
    connect(saveBtn,&QPushButton::clicked,
            this,&SettingsView::saveRequested);

    connect(scanBtn,&QPushButton::clicked,
            this,&SettingsView::scanWifiRequested);

    connect(testBtn,&QPushButton::clicked,
            this,&SettingsView::testConnectionRequested);

    connect(exitBtn,&QPushButton::clicked,
            this,&SettingsView::exitRequested);
}

void SettingsView::updateWifiList(const QStringList& list)
{
    ssidCombo->clear();
    ssidCombo->addItems(list);
}

void SettingsView::setModel(SettingsModel* model)
{
    if (!model)
        return;

    // Example binding
    ssidCombo->setCurrentText(model->ssid());
}