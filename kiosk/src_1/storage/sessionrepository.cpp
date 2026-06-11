#include "sessionrepository.h"
#include "databasemanager.h"
#include <sqlite3.h>

int SessionRepository::createSession(int patientId)
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
    return static_cast<int>(sqlite3_last_insert_rowid(db));
}
