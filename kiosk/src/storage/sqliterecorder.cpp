#include "sqliterecorder.h"
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
    //if (sqlite3_open(path, &m_db) != SQLITE_OK) {
    //    qWarning() << "SQLite open failed";
    //    m_db = nullptr;
    //    return;
    //}

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

