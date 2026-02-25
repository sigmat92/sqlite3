#include "databasemanager.h"
#include <QDebug>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager() {}
DatabaseManager::~DatabaseManager()
{
    close();
}

bool DatabaseManager::open(const QString& path)
{
    if (sqlite3_open(path.toUtf8().constData(), &m_db) != SQLITE_OK)
    {
        qDebug() << "Failed to open DB";
        return false;
    }

    return initializeSchema();
}

void DatabaseManager::close()
{
    if (m_db)
    {
        sqlite3_close(m_db);
        m_db = nullptr;
    }
}

sqlite3* DatabaseManager::connection()
{
    return m_db;
}

bool DatabaseManager::initializeSchema()
{
    const char* sql = R"(

    CREATE TABLE IF NOT EXISTS patients (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL,
        age INTEGER NOT NULL,
        mobile TEXT NOT NULL,
        gender TEXT NOT NULL,
        created_at DATETIME DEFAULT CURRENT_TIMESTAMP
    );

    CREATE TABLE IF NOT EXISTS sessions (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        patient_id INTEGER NOT NULL,
        started_at DATETIME DEFAULT CURRENT_TIMESTAMP,
        FOREIGN KEY(patient_id) REFERENCES patients(id)
    );

    CREATE TABLE IF NOT EXISTS vitals (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    session_id INTEGER NOT NULL,

    spo2 INTEGER,
    pulse INTEGER,

    systolic INTEGER,
    diastolic INTEGER,

    height INTEGER,
    weight REAL,

    temperature REAL,

    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY(session_id) REFERENCES sessions(id)
);
    )";

    char* errMsg = nullptr;

    if (sqlite3_exec(m_db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        qDebug() << "Schema error:" << errMsg;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}
