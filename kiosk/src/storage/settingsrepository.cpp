#include "settingsrepository.h"
#include "settingsrepository.h"
#include "databasemanager.h"   // 
#include <sqlite3.h>           // 
#include "model/settingsmodel.h"
#include <QSettings>

SettingsRepository::SettingsRepository(QObject* parent)
    : QObject(parent)
{
}

void SettingsRepository::save(SettingsModel* model)
{
    QSettings s("CareNest", "Kiosk");

    s.setValue("ssid", model->ssid());
    s.setValue("password", model->password());
}

void SettingsRepository::load(SettingsModel* model)
{
    QSettings s("CareNest", "Kiosk");

    model->setSsid(s.value("ssid").toString());
    model->setPassword(s.value("password").toString());
}
QString SettingsRepository::get(const QString& key)
{
    sqlite3* db = DatabaseManager::instance().connection();
    sqlite3_stmt* stmt = nullptr;

    QString result;

    const char* sql = "SELECT value FROM settings WHERE key = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, key.toStdString().c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            result = QString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        }
    }

    sqlite3_finalize(stmt);
    return result;
}
void SettingsRepository::set(const QString& key, const QString& value)
{
    sqlite3* db = DatabaseManager::instance().connection();
    sqlite3_stmt* stmt = nullptr;

    const char* sql =
        "INSERT OR REPLACE INTO settings (key, value) VALUES (?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, key.toStdString().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, value.toStdString().c_str(), -1, SQLITE_TRANSIENT);

        sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
}