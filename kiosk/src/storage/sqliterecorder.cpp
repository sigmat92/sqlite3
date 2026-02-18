#include "sqliterecorder.h"
#include <QDateTime> 
#include <QDebug>

SQLiteRecorder::SQLiteRecorder(const char* path, QObject* parent)
    : QObject(parent)
{
    open(path);
}

SQLiteRecorder::~SQLiteRecorder()
{
    if (m_db)
        sqlite3_close(m_db);
}

void SQLiteRecorder::open(const char* path)
{

     int rc = sqlite3_open(path, &m_db);
    if (rc != SQLITE_OK) {
        qWarning() << "SQLite open failed:" << sqlite3_errmsg(m_db);
        sqlite3_close(m_db);
        m_db = nullptr;
        return;
    }
    const char* sql =
        "CREATE TABLE IF NOT EXISTS scans ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "text TEXT,"
        "format TEXT,"
        "ts DATETIME DEFAULT CURRENT_TIMESTAMP);";

    sqlite3_exec(m_db, sql, nullptr, nullptr, nullptr);
}

void SQLiteRecorder::store(const QString& text, const QString& format)
{
    if (!m_db) return;

    QString q = QString("INSERT INTO scans(text,format) VALUES('%1','%2');")
                    .arg(text, format);

    sqlite3_exec(m_db, q.toUtf8().constData(), nullptr, nullptr, nullptr);
}
void SQLiteRecorder::createTables()
{
    const char* vitals_sql =
        "CREATE TABLE IF NOT EXISTS vitals ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "timestamp INTEGER,"
        "temperature REAL,"
        "temp_unit TEXT,"
        "spo2 INTEGER,"
        "pulse INTEGER,"
        "weight REAL,"
        "height INTEGER,"
        "sys INTEGER,"
        "dia INTEGER,"
        "map INTEGER);";

    char* err = nullptr;
    if (sqlite3_exec(m_db, vitals_sql, nullptr, nullptr, &err) != SQLITE_OK) {
        qDebug() << "SQLite table error:" << err;
        sqlite3_free(err);
    }
}

void SQLiteRecorder::storeVitals(double temperature, char tempUnit,
                                 int spo2, int pulse,
                                 double weight, int height,
                                 int sys, int dia, int map)
{
    if (!m_db)
        return;

    const char* sql =
        "INSERT INTO vitals "
        "(timestamp, temperature, temp_unit, spo2, pulse, "
        "weight, height, sys, dia, map) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr);

    sqlite3_bind_int64(stmt, 1, QDateTime::currentSecsSinceEpoch());
    sqlite3_bind_double(stmt, 2, temperature);
    sqlite3_bind_text(stmt, 3, QString(tempUnit).toUtf8().constData(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, spo2);
    sqlite3_bind_int(stmt, 5, pulse);
    sqlite3_bind_double(stmt, 6, weight);
    sqlite3_bind_int(stmt, 7, height);
    sqlite3_bind_int(stmt, 8, sys);
    sqlite3_bind_int(stmt, 9, dia);
    sqlite3_bind_int(stmt,10, map);

    if (sqlite3_step(stmt) != SQLITE_DONE)
        qDebug() << "SQLite insert failed";

    sqlite3_finalize(stmt);
}
