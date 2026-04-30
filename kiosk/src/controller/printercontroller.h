#pragma once

#include <QObject>
#include "service/vitalsservice.h"
#include "../service/printerservice.h"
#include "../storage/printerrepository.h"

class VitalsService;

class PrinterController : public QObject {
    Q_OBJECT

public:
        explicit PrinterController(VitalsService* vs,
                               VitalsRepository* repo,
                               QObject* parent = nullptr);
   
    void handlePrintRequest(const QString& filePath);
    QString generatePdfFromMap(const QMap<QString, QVariant>& data);

signals:
    void printCompleted();
    void printError(QString error);

public slots:   
    void onPrintRequested();
    void onThermalPrintRequested();

private:
    VitalsRepository* m_repo;
    PrinterService m_service;
    PrinterRepository printerRepo;
    VitalsService* m_vitalsService; // Add this to access vitals data for printing
};