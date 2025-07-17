#include "LogViewer.h"
#include "ui_LogViewer.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QDebug>

LogViewer::LogViewer(QWidget *parent)
    : QDialog(parent), ui(new Ui::LogViewer) {
    ui->setupUi(this);
}

LogViewer::~LogViewer() {
    delete ui;
}

void LogViewer::loadLog(const QString &dbPath) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "logviewer");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "LogViewer DB open error:" << db.lastError().text();
        return;
    }

    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("logs");
    model->select();
    model->setHeaderData(1, Qt::Horizontal, "Timestamp");
    model->setHeaderData(2, Qt::Horizontal, "Direction");
    model->setHeaderData(3, Qt::Horizontal, "Message");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

