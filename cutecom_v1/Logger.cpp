#include "Logger.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>

Logger::Logger(QObject *parent) : QObject(parent) {}

bool Logger::init(const QString &dbPath) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "Failed to open DB:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    return query.exec("CREATE TABLE IF NOT EXISTS logs ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "timestamp TEXT, "
                      "direction TEXT, "
                      "message TEXT)");
}

void Logger::log(const QString &direction, const QString &message) {
    QSqlQuery query;
    query.prepare("INSERT INTO logs (timestamp, direction, message) VALUES (?, ?, ?)");
    query.addBindValue(QDateTime::currentDateTime().toString(Qt::ISODate));
    query.addBindValue(direction);
    query.addBindValue(message);
    if (!query.exec()) {
        qDebug() << "Log insert failed:" << query.lastError().text();
    }
}

