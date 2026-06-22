#include "settingsservice.h"
#include <QProcess>
#include "model/settingsmodel.h"
#include "model/vitalsmodel.h"
#include <QApplication>
#include <QDebug>

SettingsService::SettingsService(SettingsModel* m,
                                 SettingsRepository* r,
                                 QObject* parent)
    : QObject(parent), model(m), repo(r)
{
}

void SettingsService::save()
{
    repo->save(model);
    applyNetwork();
}

void SettingsService::load()
{
    repo->load(model);
}

void SettingsService::scanWifi()
{
    QProcess proc;
    proc.start("iw wlan0 scan | grep SSID");
    proc.waitForFinished();

    QString out = proc.readAllStandardOutput();
    QStringList lines = out.split("\n");

    QStringList list;
    for(QString l : lines)
        if(l.contains("SSID:"))
            list << l.section("SSID:",1).trimmed();

    emit wifiListReady(list);
}

void SettingsService::testConnection()
{
    QProcess proc;
    proc.start("ping -c 1 8.8.8.8");
    proc.waitForFinished();

    emit connectivityResult(proc.exitCode()==0);
}

//void SettingsService::applyNetwork()
//{
//    if(model->dhcpEnabled)
//        QProcess::execute("udhcpc -i wlan0");
//}

void SettingsService::applyTheme(bool dark)
{
    if (dark)
    {
        qApp->setStyleSheet(R"(

/* ================= ROOT ================= */
QWidget {
    background-color: #000000;
    color: #FFFFFF;
    font-family: Segoe UI;
}

/* ================= HEADER / FOOTER (ALWAYS BLACK) ================= */
QWidget#appHeader,
QWidget#appFooter {
    background-color: #000000;
    color: #FFFFFF;
    border-bottom: 1px solid #222;
}

/* ================= REMOVE PANELS ================= */
/*
QWidget#patientPanel,
QWidget#metricsPanel,
QWidget#resultsPanel {
    background: transparent;
    border: none;
}
*/
QWidget#patientPanel,
QWidget#metricsPanel,
QWidget#resultsPanel {
    background-color: #101010;
    border: 1px solid #303030;
    border-radius: 10px;
    padding: 8px;
}
/* ================= TEXT ================= */
QLabel {
    color: #AAAAAA;
    font-size: 14px;
}

/* ================= STATUS ================= */
QLabel#statusLabel {
    background-color: #111111;
    border: 1px solid #303030;
    border-radius: 8px;
    color: #00FF66;
    font-size: 24px;
    font-weight: bold;
    padding: 8px;
}
/*
QLabel#statusLabel {
    color: #00FF66;
    font-size: 28px;
}
*/
/* ================= INPUT ================= */
QLineEdit {
    background: #000000;
    border: 1px solid #555;
    color: white;
    font-size: 14px;
    padding: 8px;
}
QRadioButton {
    color: #AAAAAA;
    font-size: 14px;
}
/* ================= BUTTON ================= */

QPushButton {
    background-color: #111111;
    border: 1px solid #444;
    border-radius: 8px;
    color: white;
    font-size: 18px;
    padding: 12px;
}

QPushButton:hover {
    background-color: #1A1A1A;
}

QPushButton:pressed {
    background-color: #333333;
}
/*
QPushButton {
    background: transparent;
    border: 1px solid #777;
    border-radius: 6px;
    font-size: 14px;
    padding: 12px;
    color: #FF5252;
}

QPushButton:pressed {
    border: 1px solid #FFFFFF;
}
QPushButton:disabled {
    background-color: #050505;
    color: #555555;
    border: 1px solid #222222;
}

QLineEdit:disabled {
    color: #666666;
    background-color: #111111;
}

QRadioButton:disabled {
    color: #555555;
}
*/
/* ================= ACTION BUTTON ================= */
QPushButton#newTestBtn {
    border: 1px solid #777;;
    font-weight: bold;
}

/* ================= METRIC TILE ================= */
QWidget#metricCard {
    border: 1px solid #333;
    background: #000000;
}

/* ================= BIG NUMBERS ================= */
QLabel.value {
    font-size: 52px;
    font-weight: bold;
    color: #FFFFFF;
}

/* ================= FLUORESCENT COLORS ================= */
QLabel.green { color: #00FF66; }   /* Normal */
QLabel.cyan  { color: #00E5FF; }   /* SpO2 */
QLabel.yellow{ color: #FFD600; }   /* Resp */
QLabel.red   { color: #FF5252; }   /* Critical */

QWidget#metricCard {
    background-color: #000000;
    border: 1px solid #222;
    border-radius: 6px;
}

/* TITLE */
QLabel#metricTitle {
    /*color: #666;*/
    color: #00E5FF;
    /*font-size: 14px;*/
    font-size: 18px;
}

/* VALUE (base, color overridden in code) */
QLabel#metricValue {
    font-size: 32px;
    font-weight: bold;
    color: #00FF66;
}

/* START BUTTON → TOUCH ZONE */
QPushButton#metricStartButton {
    border: 1px solid #555;
    background: transparent;
    color: #FFD600;
    font-size: 32px;
    padding: 6px;
}

QPushButton#metricStartButton:pressed {
    border: 1px solid #FFFFFF;
}

)");
    }
    else
    {
        qApp->setStyleSheet(R"(

/* ================= ROOT ================= */
QWidget {
    background-color: #E3F2FD;
    color: black;
    font-family: Segoe UI;
}

/* HEADER / FOOTER ALWAYS BLACK */
QWidget#appHeader,
QWidget#appFooter {
    background-color: #000000;
    color: #FFFFFF;
}

/* ================= PANELS ================= */
QWidget#patientPanel,
QWidget#metricsPanel,
QWidget#resultsPanel {
    background: #BBDEFB;
    border-radius: 8px;
}

/* ================= STATUS ================= */
QLabel#statusLabel {
    color: black;
    font-size: 14px;
}

/* ================= TEXT ================= */
QLabel {
    color: black;
    font-size: 14px;
}

/* ================= INPUT ================= */
QLineEdit {
    background: white;
    color: black;
    border: 1px solid #ccc;
    padding: 6px;
}
QRadioButton {
    color: black;
    font-size: 14px;
}
/* ================= BUTTON ================= */
QPushButton {
    background: #0d47a1;
    color: white;
    border-radius: 8px;
    font-size: 18px;
    padding: 10px;
}

QPushButton:hover {
    background-color: #1565c0;
}
/*
    adviceLabel->setStyleSheet(
            "color:black;"
            "font-size:24px;"
        );
*/

/* ================= METRIC ================= */
QWidget#metricCard {
    background: #E3F2FD;
    border: 1px solid #90CAF9;
}

    /* TITLE */
QLabel#metricTitle {
    /*color: #666;*/
    color: black;
    font-size: 20px;
}

/* VALUE (base, color overridden in code) */
QLabel#metricValue {
    font-size: 32px;
    font-weight: bold;
    color: black;
}
/* START BUTTON → TOUCH ZONE */
/*
QPushButton#farVisionTestBtn,
QPushButton#nearVisionTestBtn,
QPushButton#startBtn,
QPushButton {
    min-height: 60px;
    font-size: 20px;
}

QLabel#adviceLabel {
    font-size: 22px;
    font-weight: bold;
}
*/
QLabel#resultLabel {
    font-size: 24px;
    font-weight: bold;
    color: #00FF66;
}
/* ================= TABS ================= */
    QTabBar::tab {
            background-color: #0d47a1;;
            padding: 10px 25px;
            border-radius: 12px;
            font-weight: 500;
            color: white;
        }
    QTabBar::tab:selected {
            background: #4A90E2;
            color: white;
        }
)");
    }
}

void SettingsService::applyNetwork()
{
    if (!model)
        return;

    if (model->dhcpEnabled())
    {
        qDebug() << "Applying DHCP configuration...";
    }
    else
    {
        qDebug() << "Applying static IP configuration...";
    }
}
