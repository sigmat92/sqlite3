#pragma once
#include <QWidget>

class QLineEdit;
class QPushButton;
class QComboBox;
class QCheckBox;
class SettingsModel;

class SettingsView : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsView(QWidget* parent=nullptr);

    void updateWifiList(const QStringList& list);
    void setModel(SettingsModel* model);

    QLineEdit* ssidEdit;
    QLineEdit* keyEdit;
    QLineEdit* serverIpEdit;
    QLineEdit* portEdit;
    QLineEdit* deviceIpEdit;
    QLineEdit* subnetEdit;
    QLineEdit* gatewayEdit;
    QCheckBox* dhcpCheck;
    QComboBox* ssidCombo;
    

signals:
    void saveRequested();
    void scanWifiRequested();
    void testConnectionRequested();
    void exitRequested();
};

