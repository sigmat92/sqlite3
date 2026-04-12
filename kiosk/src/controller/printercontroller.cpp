#include "printercontroller.h"

PrinterController::PrinterController(QObject* parent)
    : QObject(parent) {

    connect(&m_service, &PrinterService::printSuccess,
            this, &PrinterController::printCompleted);

    connect(&m_service, &PrinterService::printFailed,
            this, &PrinterController::printError);
}

void PrinterController::handlePrintRequest(const QString& filePath) {
    PrintJob job;
    job.filePath = filePath;
    job.printerIp = "192.168.1.100"; // configurable

    m_repo.saveJob(job);
    m_service.print(job);
}