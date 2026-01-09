#pragma once

#include <QObject>
#include <sqlite3.h>

class SQLiteRecorder : public QObject
{
    Q_OBJECT

public:
    explicit SQLiteRecorder(const char* path, QObject* parent = nullptr);
    ~SQLiteRecorder();

public slots:
    void store(const QString& text, const QString& format);

private:
    void open(const char* path);
    sqlite3* m_db = nullptr;
};

