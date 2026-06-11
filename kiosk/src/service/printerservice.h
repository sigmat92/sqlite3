#pragma once

#include <QObject>
#include "../model/printjob.h"

class PrinterService : public QObject {
    Q_OBJECT

public:
    explicit PrinterService(QObject* parent = nullptr);

    bool print(const PrintJob& job);
    
    bool printReport(
        const QString& text);
private:

    bool createPGM(
        const QString& text);

    bool createPWG();
signals:
    void printSuccess();
    void printFailed(QString error);
};