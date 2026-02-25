#include "vitalsrepository.h"
#include "databasemanager.h"

bool VitalsRepository::saveSpO2(int sessionId, int spo2, int pulse)
{
    sqlite3* db = DatabaseManager::instance().connection();

    const char* sql =
        "INSERT INTO vitals (session_id, spo2, pulse) "
        "VALUES (?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, sessionId);
    sqlite3_bind_int(stmt, 2, spo2);
    sqlite3_bind_int(stmt, 3, pulse);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);
    return ok;
}

bool VitalsRepository::saveTemperature(int sessionId, double temperature)
{
    sqlite3* db = DatabaseManager::instance().connection();

    const char* sql =
        "INSERT INTO vitals (session_id, temperature) "
        "VALUES (?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, sessionId);
    sqlite3_bind_double(stmt, 2, temperature);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);
    return ok;
}

bool VitalsRepository::saveWeight(int sessionId, double weight)
{
    sqlite3* db = DatabaseManager::instance().connection();

    const char* sql =
        "INSERT INTO vitals (session_id, weight) "
        "VALUES (?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, sessionId);
    sqlite3_bind_double(stmt, 2, weight);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);
    return ok;
}

bool VitalsRepository::saveHeight(int sessionId, int height)
{
    sqlite3* db = DatabaseManager::instance().connection();

    const char* sql =
        "INSERT INTO vitals (session_id, height) "
        "VALUES (?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, sessionId);
    sqlite3_bind_int(stmt, 2, height);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);
    return ok;
}

bool VitalsRepository::saveNIBP(int sessionId, int systolic, int diastolic)
{
    sqlite3* db = DatabaseManager::instance().connection();

    const char* sql =
        "INSERT INTO vitals (session_id, systolic, diastolic) "
        "VALUES (?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, sessionId);
    sqlite3_bind_int(stmt, 2, systolic);
    sqlite3_bind_int(stmt, 3, diastolic);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);
    return ok;
}
