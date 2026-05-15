#pragma once

#include <QObject>
#include "service/vitalsservice.h"
#include "../service/printerservice.h"
#include "../storage/printerrepository.h"

class VitalsService;
class PrinterService;

class PrinterController : public QObject {
    Q_OBJECT

public:
        explicit PrinterController(VitalsService* vs,
                               VitalsRepository* repo,
                               QObject* parent = nullptr);
   
    void handlePrintRequest(const QString& filePath);
    QString generatePdfFromMap(const QMap<QString, QVariant>& data);

    void setPrinterService(PrinterService* s)
    {
        m_printerService = s;
    }

signals:
    void printCompleted();
    void printError(QString error);

public slots:   
    //void onPrintRequested();
    void onThermalPrintRequested();
    void onNetworkPrintRequested();

private:

    PrinterService* m_printerService = nullptr;
    VitalsRepository* m_repo;
    
    PrinterRepository printerRepo;
    VitalsService* m_vitalsService; 
};