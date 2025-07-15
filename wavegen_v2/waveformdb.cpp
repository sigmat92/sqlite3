#include "waveformdb.h"
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>

WaveformDB::WaveformDB() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "Failed to open DB:" << db.lastError().text();
        return;
    }
    ensureTable();
}

WaveformDB& WaveformDB::instance() {
    static WaveformDB inst;
    return inst;
}

void WaveformDB::ensureTable() {
    QSqlQuery q;
    q.exec("CREATE TABLE IF NOT EXISTS waveforms (name TEXT PRIMARY KEY, data TEXT)");
}

void WaveformDB::save(const QString& name, const QVector<double>& waveform) {
    QJsonArray arr;
    for (double d : waveform)
        arr.append(d);
    QJsonDocument doc(arr);
    QString json = doc.toJson(QJsonDocument::Compact);

    QSqlQuery q;
    q.prepare("REPLACE INTO waveforms (name, data) VALUES (?, ?)");
    q.addBindValue(name);
    q.addBindValue(json);
    if (!q.exec()) {
        qDebug() << "Save error:" << q.lastError().text();
    }
}

QVector<double> WaveformDB::load(const QString& name) {
    QVector<double> result;
    QSqlQuery q;
    q.prepare("SELECT data FROM waveforms WHERE name = ?");
    q.addBindValue(name);
    if (q.exec() && q.next()) {
        QString json = q.value(0).toString();
        QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
        QJsonArray arr = doc.array();
        for (const auto& val : arr)
            result.append(val.toDouble());
    }
    return result;
}

QStringList WaveformDB::listWaveforms() const {
    QStringList list;
    QSqlQuery q("SELECT name FROM waveforms");
    while (q.next())
        list << q.value(0).toString();
    return list;
}