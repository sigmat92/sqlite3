#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QSqlDatabase>

class Logger : public QObject {
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);
    bool init(const QString &dbPath);
    void log(const QString &direction, const QString &message);

private:
    QSqlDatabase db;
};

#endif // LOGGER_H

