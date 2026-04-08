#include "vitalsrepository.h"
#include "databasemanager.h"
#include <vector>
#include "record.h"
#include <sqlite3.h>

/* -------- HELPER: ENSURE ROW EXISTS -------- */

static void ensureRow(int sessionId)
{
    sqlite3* db = DatabaseManager::instance().connection();

    sqlite3_stmt* stmt = nullptr;

    const char* sql =
        "INSERT OR IGNORE INTO vitals (session_id) VALUES (?);";

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, sessionId);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

/* -------- TEMPERATURE -------- */

bool VitalsRepository::saveTemperature(int sessionId, double temperature)
{
    qDebug() << " Actual Saving TEMP  from VitalsRepository:" << temperature;
    qDebug() << "SessionId in DB:" << sessionId;
    ensureRow(sessionId);

    sqlite3* db = DatabaseManager::instance().connection();

    const char* sql =
        "UPDATE vitals SET temperature=? WHERE session_id=?;";

    sqlite3_stmt* stmt = nullptr;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_double(stmt, 1, temperature);
    sqlite3_bind_int(stmt, 2, sessionId);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);
    return ok;
}

/* -------- SPO2 -------- */

bool VitalsRepository::saveSpO2(int sessionId, int spo2, int pulse)
{
    ensureRow(sessionId);

    sqlite3* db = DatabaseManager::instance().connection();

    const char* sql =
        "UPDATE vitals SET spo2=?, pulse=? WHERE session_id=?;";

    sqlite3_stmt* stmt = nullptr;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, spo2);
    sqlite3_bind_int(stmt, 2, pulse);
    sqlite3_bind_int(stmt, 3, sessionId);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);
    return ok;
}

/* -------- WEIGHT -------- */

bool VitalsRepository::saveWeight(int sessionId, double weight)
{
    ensureRow(sessionId);

    sqlite3* db = DatabaseManager::instance().connection();

    const char* sql =
        "UPDATE vitals SET weight=? WHERE session_id=?;";

    sqlite3_stmt* stmt = nullptr;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_double(stmt, 1, weight);
    sqlite3_bind_int(stmt, 2, sessionId);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);
    return ok;
}

/* -------- HEIGHT -------- */

bool VitalsRepository::saveHeight(int sessionId, int height)
{
    ensureRow(sessionId);

    sqlite3* db = DatabaseManager::instance().connection();

    const char* sql =
        "UPDATE vitals SET height=? WHERE session_id=?;";

    sqlite3_stmt* stmt = nullptr;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, height);
    sqlite3_bind_int(stmt, 2, sessionId);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);
    return ok;
}

/* -------- NIBP -------- */

bool VitalsRepository::saveNIBP(int sessionId, int systolic, int diastolic)
{
    ensureRow(sessionId);

    sqlite3* db = DatabaseManager::instance().connection();

    const char* sql =
        "UPDATE vitals SET systolic=?, diastolic=? WHERE session_id=?;";

    sqlite3_stmt* stmt = nullptr;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, systolic);
    sqlite3_bind_int(stmt, 2, diastolic);
    sqlite3_bind_int(stmt, 3, sessionId);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);
    return ok;
}
//
QVariantMap VitalsRepository::getLatestVitals(int sessionId)
{
    QVariantMap data;

    sqlite3* db = DatabaseManager::instance().connection();
    sqlite3_stmt* stmt = nullptr;

    const char* sql =
        "SELECT v.temperature, v.spo2, v.pulse, "
        "v.systolic, v.diastolic, v.height, v.weight, "
        "p.name, p.age, p.mobile, p.gender "
        "FROM vitals v "
        "JOIN sessions s ON v.session_id = s.id "
        "JOIN patients p ON s.patient_id = p.id "
        "WHERE v.session_id=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return data;

    sqlite3_bind_int(stmt, 1, sessionId);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        // -------- VITALS --------
        data["temperature"] = sqlite3_column_double(stmt, 0);
        data["spo2"]        = sqlite3_column_int(stmt, 1);
        data["pulse"]       = sqlite3_column_int(stmt, 2);
        data["sys"]         = sqlite3_column_int(stmt, 3);
        data["dia"]         = sqlite3_column_int(stmt, 4);
        data["height"]      = sqlite3_column_int(stmt, 5);
        data["weight"]      = sqlite3_column_double(stmt, 6);

        // -------- PATIENT --------
        data["name"]   = QString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        data["age"]    = sqlite3_column_int(stmt, 8);
        data["mobile"] = QString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        data["gender"] = QString(reinterpret_cast<const char*>(sqlite3_column_text(stmt,10)));
    }

    sqlite3_finalize(stmt);
    return data;
}
//
/*
QVariantMap VitalsRepository::getLatestVitals(int sessionId)
{
    QVariantMap data;

    sqlite3* db = DatabaseManager::instance().connection();
    sqlite3_stmt* stmt = nullptr;

    const char* sql =
        "SELECT temperature, spo2, pulse, "
        "systolic, diastolic, height, weight "
        "FROM vitals WHERE session_id=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return data;

    sqlite3_bind_int(stmt, 1, sessionId);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        data["temperature"] = sqlite3_column_double(stmt, 0);
        data["spo2"]        = sqlite3_column_int(stmt, 1);
        data["pulse"]       = sqlite3_column_int(stmt, 2);
        data["sys"]         = sqlite3_column_int(stmt, 3);
        data["dia"]         = sqlite3_column_int(stmt, 4);
        data["height"]      = sqlite3_column_int(stmt, 5);
        data["weight"]      = sqlite3_column_double(stmt, 6);
    }

    sqlite3_finalize(stmt);

    return data;
}
*/
bool VitalsRepository::createEmptyVitals(int sessionId)
{
    sqlite3* db = DatabaseManager::instance().connection();

    const char* sql =
        "INSERT INTO vitals (session_id) VALUES (?);";

    sqlite3_stmt* stmt = nullptr;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, sessionId);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;

    sqlite3_finalize(stmt);

    return ok;
}