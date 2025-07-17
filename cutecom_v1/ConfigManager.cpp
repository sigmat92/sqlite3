#include "ConfigManager.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

ConfigManager::ConfigManager(QObject *parent) : QObject(parent) {}

void ConfigManager::save(const QString &filePath, MainWindow *mainWindow) {
    Ui::MainWindow *ui = mainWindow->getUi();

    QJsonObject obj;
    obj["port"] = ui->portComboBox->currentText();
    obj["baudrate"] = ui->baudRateBox->currentText();

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(obj).toJson());
        file.close();
    }
}

void ConfigManager::load(const QString &filePath, MainWindow *mainWindow) {
    Ui::MainWindow *ui = mainWindow->getUi();

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject obj = doc.object();
        file.close();

        ui->portComboBox->setCurrentText(obj["port"].toString());
        ui->baudRateBox->setCurrentText(obj["baudrate"].toString());
    }
}

