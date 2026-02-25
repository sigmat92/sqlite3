#include "settingsview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTabWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QIntValidator>

SettingsView::SettingsView(QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle("Carenest mini");
    resize(620, 340);

    setStyleSheet(R"(
        QWidget {
            font-size: 16px;
        }
        QTabBar::tab {
            background: #147da7;
            padding: 10px;
            min-width: 150px;
        }
        QTabBar::tab:selected {
            background: #021a39;
            color: white;
        }
        QGroupBox {
            font-weight: bold;
            margin-top: 15px;
        }
        QPushButton {
            background-color: #2ccfe5;
            color: white;
            padding: 8px 15px;
        }
    )");

    setupUI();
}
void SettingsView::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    m_tabs = new QTabWidget;
    m_tabs->addTab(createCommTab(), "Comm Settings");
    m_tabs->addTab(new QWidget, "Date & Time");
    m_tabs->addTab(new QWidget, "Calibration");
    

    mainLayout->addWidget(m_tabs);
}
QWidget* SettingsView::createCommTab()
{
    QWidget* tab = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(tab);

    // WIFI SECTION
    QGroupBox* wifiBox = new QGroupBox("WIFI SETTINGS");
    QGridLayout* wifiLayout = new QGridLayout(wifiBox);

    m_ssid = new QLineEdit;
    m_key  = new QLineEdit;
    m_key->setEchoMode(QLineEdit::Password);

    wifiLayout->addWidget(new QLabel("SSID:"),0,0);
    wifiLayout->addWidget(m_ssid,0,1);

    wifiLayout->addWidget(new QLabel("Security:"),1,0);
    wifiLayout->addWidget(new QLabel("WPA/WPA2"),1,1);

    wifiLayout->addWidget(new QLabel("Security Key:"),2,0);
    wifiLayout->addWidget(m_key,2,1);

    QPushButton* connectBtn = new QPushButton("Connect");
    wifiLayout->addWidget(connectBtn,3,1);

    layout->addWidget(wifiBox);

    // SERVER SECTION
    QGroupBox* serverBox = new QGroupBox("SERVER SETTINGS");
    QGridLayout* serverLayout = new QGridLayout(serverBox);

    serverLayout->addWidget(new QLabel("IP Address:"),0,0);
    serverLayout->addWidget(createIPRow(
        m_serverIp1,m_serverIp2,
        m_serverIp3,m_serverIp4),0,1);

    m_port = new QLineEdit;
    m_port->setValidator(new QIntValidator(1,65535,this));

    serverLayout->addWidget(new QLabel("Port No:"),1,0);
    serverLayout->addWidget(m_port,1,1);

    layout->addWidget(serverBox);

    // DEVICE SECTION
    QGroupBox* deviceBox = new QGroupBox("DEVICE SETTINGS");
    QGridLayout* deviceLayout = new QGridLayout(deviceBox);

    deviceLayout->addWidget(new QLabel("IP Address:"),0,0);
    deviceLayout->addWidget(createIPRow(
        m_devIp1,m_devIp2,
        m_devIp3,m_devIp4),0,1);

    deviceLayout->addWidget(new QLabel("Subnet Mask:"),1,0);
    deviceLayout->addWidget(createIPRow(
        m_mask1,m_mask2,
        m_mask3,m_mask4),1,1);

    deviceLayout->addWidget(new QLabel("Gateway:"),2,0);
    deviceLayout->addWidget(createIPRow(
        m_gate1,m_gate2,
        m_gate3,m_gate4),2,1);

    m_dhcpBtn = new QPushButton("ENABLE DHCP");
    deviceLayout->addWidget(m_dhcpBtn,3,1);

    QHBoxLayout* bottomBtns = new QHBoxLayout;
    QPushButton* saveBtn = new QPushButton("SAVE");
    QPushButton* exitBtn = new QPushButton("EXIT");

    bottomBtns->addWidget(saveBtn);
    bottomBtns->addWidget(exitBtn);

    deviceLayout->addLayout(bottomBtns,4,1);

    layout->addWidget(deviceBox);

    layout->addStretch();
//
connect(connectBtn, &QPushButton::clicked, this, [=]()
{
    emit wifiConnectRequested(m_ssid->text(),
                              m_key->text());
});

connect(m_dhcpBtn, &QPushButton::clicked, this, [=]()
{
    emit dhcpToggled(true);
});

connect(saveBtn, &QPushButton::clicked, this, [=]()
{
    QString ip = m_devIp1->text() + "." +
                 m_devIp2->text() + "." +
                 m_devIp3->text() + "." +
                 m_devIp4->text();

    QString mask = m_mask1->text() + "." +
                   m_mask2->text() + "." +
                   m_mask3->text() + "." +
                   m_mask4->text();

    QString gateway = m_gate1->text() + "." +
                      m_gate2->text() + "." +
                      m_gate3->text() + "." +
                      m_gate4->text();

    emit staticIPRequested(ip, mask, gateway);
});
//
    return tab;
}
QWidget* SettingsView::createIPRow(QLineEdit*& a,
                                   QLineEdit*& b,
                                   QLineEdit*& c,
                                   QLineEdit*& d)
{
    QWidget* row = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout(row);

    auto makeField = [this]() {
        QLineEdit* e = new QLineEdit;
        e->setFixedWidth(50);
        e->setValidator(new QIntValidator(0,255,this));
        return e;
    };

    a = makeField();
    b = makeField();
    c = makeField();
    d = makeField();

    layout->addWidget(a);
    layout->addWidget(new QLabel("."));
    layout->addWidget(b);
    layout->addWidget(new QLabel("."));
    layout->addWidget(c);
    layout->addWidget(new QLabel("."));
    layout->addWidget(d);

    return row;
}
void SettingsView::lockControls()
{
    m_ssid->setEnabled(false);
    m_key->setEnabled(false);
    m_dhcpBtn->setEnabled(false);

    m_serverIp1->setEnabled(false);
    m_serverIp2->setEnabled(false);
    m_serverIp3->setEnabled(false);
    m_serverIp4->setEnabled(false);
    m_port->setEnabled(false);

    m_devIp1->setEnabled(false);
    m_devIp2->setEnabled(false);
    m_devIp3->setEnabled(false);
    m_devIp4->setEnabled(false);

    m_mask1->setEnabled(false);
    m_mask2->setEnabled(false);
    m_mask3->setEnabled(false);
    m_mask4->setEnabled(false);

    m_gate1->setEnabled(false);
    m_gate2->setEnabled(false);
    m_gate3->setEnabled(false);
    m_gate4->setEnabled(false);
}

void SettingsView::unlockControls()
{
    m_ssid->setEnabled(true);
    m_key->setEnabled(true);
    m_dhcpBtn->setEnabled(true);

    m_serverIp1->setEnabled(true);
    m_serverIp2->setEnabled(true);
    m_serverIp3->setEnabled(true);
    m_serverIp4->setEnabled(true);
    m_port->setEnabled(true);

    m_devIp1->setEnabled(true);
    m_devIp2->setEnabled(true);
    m_devIp3->setEnabled(true);
    m_devIp4->setEnabled(true);

    m_mask1->setEnabled(true);
    m_mask2->setEnabled(true);
    m_mask3->setEnabled(true);
    m_mask4->setEnabled(true);

    m_gate1->setEnabled(true);
    m_gate2->setEnabled(true);
    m_gate3->setEnabled(true);
    m_gate4->setEnabled(true);
}
