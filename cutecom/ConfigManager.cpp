#include "ConfigManager.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

ConfigManager::ConfigManager(QObject *parent) : QObject(parent) {}

void ConfigManager::save(const QString &filePath, MainWindow *mainWindow) {
    Ui::MainWindow *ui = mainWindow->getUi();

    QJsonObject obj;
    obj["port"] = ui->portComboBox->currentText();
    obj["baud"] = ui->baudRateBox->currentText();
    obj["autoSend"] = ui->autoSendCheck->isChecked();
    obj["interval"] = ui->intervalSpin->value();

    QJsonDocument doc(obj);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void ConfigManager::load(const QString &filePath, MainWindow *mainWindow) {
    Ui::MainWindow *ui = mainWindow->getUi();

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject obj = doc.object();
        ui->portComboBox->setCurrentText(obj["port"].toString());
        ui->baudRateBox->setCurrentText(obj["baud"].toString());
        ui->autoSendCheck->setChecked(obj["autoSend"].toBool());
        ui->intervalSpin->setValue(obj["interval"].toInt());
        file.close();
    }
}