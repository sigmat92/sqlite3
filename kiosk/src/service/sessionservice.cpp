
#include "sessionservice.h"
#include "vitalsservice.h"
#include <QDebug>
#include "sessionservice.h"
#include "storage/databasemanager.h"
#include <sqlite3.h>
#include "storage/sessionrepository.h"

SessionService::SessionService(SessionRepository* repo, QObject* parent)
    : QObject(parent),
      m_repo(repo)
{
}

void SessionService::startSpo2()
{
    qDebug() << "SessionService: Starting SpO2 measurement";

    auto* vitalsService = parent() ? parent()->findChild<VitalsService*>() : nullptr;
    if (!vitalsService)
    {
        qWarning() << "SessionService: VitalsService not found for SpO2 measurement";
        return;
    }

    vitalsService->requestSpo2();
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

int SessionService::createSession(int patientId)
{
    qDebug() << "Creating NEW session in DB...";

    int sessionId = m_repo->createSession(patientId);

    qDebug() << "Session created:" << sessionId;

    return sessionId;
}

/*
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
*/