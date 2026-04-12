#include "printerrepository.h"
#include <QDebug>

void PrinterRepository::saveJob(const PrintJob& job) {
    qDebug() << "Saving print job:" << job.filePath;
    // Extend: SQLite logging if needed
}