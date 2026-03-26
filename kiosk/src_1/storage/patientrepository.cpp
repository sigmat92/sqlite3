#include "patientrepository.h"
#include "databasemanager.h"

#include <sqlite3.h>
#include <QDebug>

PatientRepository::PatientRepository()
{
}



bool PatientRepository::saveVitals(int patientId,
                                   int spo2,
                                   int pulse)
{
    sqlite3* db = DatabaseManager::instance().connection();

    if (!db)
        return false;

    const char* sql =
        "INSERT INTO vitals (patient_id, spo2, pulse) "
        "VALUES (?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        qDebug() << "Prepare failed:" << sqlite3_errmsg(db);
        return false;
    }

    sqlite3_bind_int(stmt, 1, patientId);
    sqlite3_bind_int(stmt, 2, spo2);
    sqlite3_bind_int(stmt, 3, pulse);

    bool success = true;

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        qDebug() << "Insert vitals failed:" << sqlite3_errmsg(db);
        success = false;
    }

    sqlite3_finalize(stmt);

    return success;
}

int PatientRepository::savePatient(const QString& name,
                                   int age,
                                   const QString& mobile,
                                   const QString& gender)
{
    sqlite3* db = DatabaseManager::instance().connection();

    const char* sql =
        "INSERT INTO patients (name, age, mobile, gender) "
        "VALUES (?, ?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return -1;

    sqlite3_bind_text(stmt, 1, name.toUtf8().constData(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, age);
    sqlite3_bind_text(stmt, 3, mobile.toUtf8().constData(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, gender.toUtf8().constData(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);

    return (int)sqlite3_last_insert_rowid(db);
}