#pragma once

#include <QObject>
#include "../service/printerservice.h"
#include "../storage/printerrepository.h"

class PrinterController : public QObject {
    Q_OBJECT

public:
    explicit PrinterController(QObject* parent = nullptr);

    void handlePrintRequest(const QString& filePath);

signals:
    void printCompleted();
    void printError(QString error);

private:
    PrinterService m_service;
    PrinterRepository m_repo;
};