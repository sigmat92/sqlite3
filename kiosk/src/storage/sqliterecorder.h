#pragma once

#include <QObject>
#include <sqlite3.h>
#include <QString>
//#include "model/settingsmodel.h"

class SQLiteRecorder : public QObject
{
    Q_OBJECT

public:
    explicit SQLiteRecorder(const char* path, QObject* parent = nullptr);
    ~SQLiteRecorder();

public slots:
    void store(const QString& text, const QString& format);
    void storeVitals(double temperature, char tempUnit,
                     int spo2, int pulse,
                     double weight, int height,
                     int sys, int dia, int map);
    //void storeSettings(QString ssid,
    //               QString key,
    //               QString serverIp,
    //               int port,
    //               bool dhcp);

    //bool loadSettings(SettingsModel* model);


private:
    void open(const char* path);
    void createTables();
    sqlite3* m_db = nullptr;
};

