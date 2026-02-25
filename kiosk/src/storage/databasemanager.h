#pragma once

#include <QString>
#include <sqlite3.h>

class DatabaseManager
{
public:
    static DatabaseManager& instance();

    bool open(const QString& path);
    void close();
    sqlite3* connection();

private:
    DatabaseManager();
    ~DatabaseManager();

    bool initializeSchema();

    sqlite3* m_db = nullptr;
};
