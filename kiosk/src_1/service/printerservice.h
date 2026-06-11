#pragma once

#include <QObject>
#include "../model/printjob.h"

class PrinterService : public QObject {
    Q_OBJECT

public:
    explicit PrinterService(QObject* parent = nullptr);

    bool print(const PrintJob& job);

signals:
    void printSuccess();
    void printFailed(QString error);
};