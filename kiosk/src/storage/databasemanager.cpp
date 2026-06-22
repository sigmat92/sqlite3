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

/*  UPDATED SCHEMA (IMPORTANT) */

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

    /* ONE ROW PER SESSION */
    CREATE TABLE IF NOT EXISTS vitals (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        session_id INTEGER UNIQUE NOT NULL,

        spo2 INTEGER,
        pulse INTEGER,

        systolic INTEGER,
        diastolic INTEGER,

        height INTEGER,
        weight REAL,

        temperature REAL,

        far_vision TEXT,
        near_vision TEXT,

        created_at DATETIME DEFAULT CURRENT_TIMESTAMP,

        FOREIGN KEY(session_id) REFERENCES sessions(id)
    );
/* results */
        CREATE TABLE IF NOT EXISTS results (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        session_id INTEGER UNIQUE NOT NULL,
        
        body_mass_index REAL,
        basal_metabolic_rate REAL,
        bmi_analysis REAL,
        body_surface_area REAL,
        far_vision TEXT,
        near_vision TEXT
        
        created_at DATETIME DEFAULT CURRENT_TIMESTAMP,

        FOREIGN KEY(session_id) REFERENCES sessions(id)
    );
    /* For storing settings like WiFi, server, theme etc. */
    CREATE TABLE IF NOT EXISTS settings (
    key TEXT PRIMARY KEY,
    value TEXT
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