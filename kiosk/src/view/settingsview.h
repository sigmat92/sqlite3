#pragma once
#include <QWidget>

class QTabWidget;
class QLineEdit;
class QPushButton;
class QLabel;

class SettingsView : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsView(QWidget* parent = nullptr);

    void unlockControls();
    void lockControls();

signals:
    void adminLoginRequested(QString pin);
    void wifiConnectRequested(QString ssid, QString pass);
    void dhcpToggled(bool enabled);
    void staticIPRequested(QString ip, QString mask, QString gateway);

private:
    void setupUI();
    QWidget* createCommTab();
    QWidget* createIPRow(QLineEdit*& a,
                         QLineEdit*& b,
                         QLineEdit*& c,
                         QLineEdit*& d);

    QTabWidget* m_tabs;

    QLineEdit* m_ssid;
    QLineEdit* m_key;

    QLineEdit* m_serverIp1;
    QLineEdit* m_serverIp2;
    QLineEdit* m_serverIp3;
    QLineEdit* m_serverIp4;
    QLineEdit* m_port;

    QLineEdit* m_devIp1;
    QLineEdit* m_devIp2;
    QLineEdit* m_devIp3;
    QLineEdit* m_devIp4;

    QLineEdit* m_mask1;
    QLineEdit* m_mask2;
    QLineEdit* m_mask3;
    QLineEdit* m_mask4;

    QLineEdit* m_gate1;
    QLineEdit* m_gate2;
    QLineEdit* m_gate3;
    QLineEdit* m_gate4;

    QPushButton* m_dhcpBtn;
};