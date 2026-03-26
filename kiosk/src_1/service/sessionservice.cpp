
#include "sessionservice.h"
#include <QDebug>

SessionService::SessionService(QObject* parent)
    : QObject(parent)
{
}

void SessionService::startSpo2()
{
    qDebug() << "SessionService: Starting SpO2 measurement";
    // TODO: trigger SpO2 device
}

void SessionService::startNibp()
{
    qDebug() << "SessionService: Starting NIBP measurement";
}

void SessionService::startHeight()
{
    qDebug() << "SessionService: Starting Height measurement";
}

void SessionService::startWeight()
{
    qDebug() << "SessionService: Starting Weight measurement";
}

void SessionService::startTemperature()
{
    qDebug() << "SessionService: Starting Temperature measurement";
}

#include "sessionservice.h"
#include "storage/databasemanager.h"
#include <sqlite3.h>

int SessionService::createSession(int patientId)
{
    sqlite3* db = DatabaseManager::instance().connection();

    const char* sql =
        "INSERT INTO sessions (patient_id) VALUES (?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return -1;

    sqlite3_bind_int(stmt, 1, patientId);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);

    return (int)sqlite3_last_insert_rowid(db);
}
