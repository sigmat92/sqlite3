#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QString>

class MainWindow;

class ConfigManager : public QObject {
    Q_OBJECT

public:
    explicit ConfigManager(QObject *parent = nullptr);
    void save(const QString &filePath, MainWindow *mainWindow);
    void load(const QString &filePath, MainWindow *mainWindow);
};

#endif // CONFIGMANAGER_H