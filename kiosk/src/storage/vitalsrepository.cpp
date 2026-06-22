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
//vision
bool VitalsRepository::saveVision(
        int sessionId,
        const QString& far,
        const QString& near)
{
    sqlite3 *db = DatabaseManager::instance().connection();

    sqlite3_stmt *stmt = nullptr;

    const char *updateSql =
        "UPDATE vitals "
        "SET far_vision=?, "
        "near_vision=? "
        "WHERE session_id=?;";

    sqlite3_prepare_v2(db, updateSql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt,1,
                      far.toUtf8().constData(),
                      -1,SQLITE_TRANSIENT);

    sqlite3_bind_text(stmt,2,
                      near.toUtf8().constData(),
                      -1,SQLITE_TRANSIENT);

    sqlite3_bind_int(stmt,3,sessionId);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if(sqlite3_changes(db) > 0)
    {
        qDebug() << "Vision updated";
        return true;
    }

    qDebug() << "No vitals row found. Creating one...";
    //Then insert a new row:
        const char *insertSql =
        "INSERT INTO vitals("
        "session_id,"
        "far_vision,"
        "near_vision)"
        "VALUES(?,?,?);";

    sqlite3_prepare_v2(db, insertSql, -1, &stmt, nullptr);

    sqlite3_bind_int(stmt,1,sessionId);

    sqlite3_bind_text(stmt,2,
                      far.toUtf8().constData(),
                      -1,SQLITE_TRANSIENT);

    sqlite3_bind_text(stmt,3,
                      near.toUtf8().constData(),
                      -1,SQLITE_TRANSIENT);

    bool ok =
        sqlite3_step(stmt)==SQLITE_DONE;

    sqlite3_finalize(stmt);

    return ok;
}
/*
bool VitalsRepository::saveVision(
        int sessionId,
        const QString& far,
        const QString& near)
{
    qDebug()
    << "[DB SAVE]"
    << sessionId
    << near
    << far;
    sqlite3 *db = DatabaseManager::instance().connection();

    sqlite3_stmt *stmt = nullptr;
    
    const char *sql =
        "UPDATE vitals "
        "SET far_vision=?,"
        "near_vision=? "
        "WHERE session_id=?;";
    
    if(sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr)!=SQLITE_OK)
        return false;

    //qDebug()
    //<< "Rows changed ="
    //<< sqlite3_changes(db);
    
    sqlite3_bind_text(stmt,1,
        far.toUtf8().constData(),-1,
        SQLITE_TRANSIENT);

    sqlite3_bind_text(stmt,2,
        near.toUtf8().constData(),-1,
        SQLITE_TRANSIENT);

    sqlite3_bind_int(stmt,3,sessionId);

    //bool ok =
    //    sqlite3_step(stmt)==SQLITE_DONE;

    //sqlite3_finalize(stmt);

    

    bool ok =
    sqlite3_step(stmt) == SQLITE_DONE;

        qDebug() << "step =" << ok;
        qDebug() << "Rows changed =" << sqlite3_changes(db);

        sqlite3_finalize(stmt);
        return ok;
}
*/
QVariantMap VitalsRepository::getLatestVitals(int sessionId)
{

    qDebug() << "Looking up session:" << sessionId;
    QVariantMap data;

    sqlite3* db = DatabaseManager::instance().connection();
    sqlite3_stmt* stmt = nullptr;
    
const char* sql =
    "SELECT "
    "s.id, "
    "p.id, "
    "v.temperature, "
    "v.spo2, "
    "v.pulse, "
    "v.systolic, "
    "v.diastolic, "
    "v.height, "
    "v.weight, "
    "v.far_vision, "
    "v.near_vision, "
    "p.name, "
    "p.age, "
    "p.mobile, "
    "p.gender "
    "FROM sessions s "
    "JOIN patients p ON s.patient_id = p.id "
    "LEFT JOIN vitals v ON v.session_id = s.id "
    "WHERE s.id=? "
    "ORDER BY v.id DESC LIMIT 1;";
    

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        {
            qDebug()
                << "Prepare failed:"
                << sqlite3_errmsg(db);

            return data;
        }
    //if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    //    return data;

    sqlite3_bind_int(stmt, 1, sessionId);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        //data["sessionId"] = sqlite3_column_int(stmt,0);
        data["sessionId"] = sqlite3_column_type(stmt,0) != SQLITE_NULL ? sqlite3_column_int(stmt,0) : 0;
        //data["patientId"] = sqlite3_column_int(stmt,1);
        data["patientId"] = sqlite3_column_type(stmt,1) != SQLITE_NULL ? sqlite3_column_int(stmt,1) : 0;
        // -------- VITALS --------
        data["temperature"] = sqlite3_column_type(stmt,2) != SQLITE_NULL ? sqlite3_column_double(stmt,2) : 0;
        data["spo2"]        = sqlite3_column_type(stmt,3) != SQLITE_NULL ? sqlite3_column_int(stmt,3) : 0;
        data["pulse"]       = sqlite3_column_type(stmt,4) != SQLITE_NULL ? sqlite3_column_int(stmt,4) : 0;
        data["systolic"]    = sqlite3_column_type(stmt,5) != SQLITE_NULL ? sqlite3_column_int(stmt,5) : 0;
        data["diastolic"]   = sqlite3_column_type(stmt,6) != SQLITE_NULL ? sqlite3_column_int(stmt,6) : 0;
        data["height"]      = sqlite3_column_type(stmt,7) != SQLITE_NULL ? sqlite3_column_int(stmt,7) : 0;
        data["weight"]      = sqlite3_column_type(stmt,8) != SQLITE_NULL ? sqlite3_column_double(stmt,8) : 0;
        //data["farVision"] = sqlite3_column_type(stmt,9) != SQLITE_NULL ? sqlite3_column_double(stmt,9) : 0;
        //data["nearVision"] = sqlite3_column_type(stmt,10) != SQLITE_NULL ? sqlite3_column_double(stmt,10) : 0;
        data["farVision"] =
        sqlite3_column_text(stmt,9)
            ? QString(reinterpret_cast<const char*>(
                sqlite3_column_text(stmt,9)))
            : "--";

        data["nearVision"] =
            sqlite3_column_text(stmt,10)
                ? QString(reinterpret_cast<const char*>(
                    sqlite3_column_text(stmt,10)))
                : "--";
        // -------- PATIENT --------
        data["name"]   = sqlite3_column_text(stmt,11) ? QString(reinterpret_cast<const char*>(sqlite3_column_text(stmt,11))) : "";
        data["age"]    = sqlite3_column_type(stmt,12) != SQLITE_NULL ? sqlite3_column_int(stmt,12) : 0;
        data["mobile"] = sqlite3_column_text(stmt,13) ? QString(reinterpret_cast<const char*>(sqlite3_column_text(stmt,13))) : "";
        data["gender"] = sqlite3_column_text(stmt,14)? QString(reinterpret_cast<const char*>(sqlite3_column_text(stmt,14))) : "";
    }

    sqlite3_finalize(stmt);
    
    return data;
}
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
/*
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
*/
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
/*
QVariantMap VitalsRepository::getVitalsForSession(int sessionId)
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