#include "controller/printercontroller.h"

#include "view/printview.h"
#include <QDebug>
#include "service/vitalsservice.h"
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QMap>
#include <QVariant>

//PrinterController::PrinterController(QObject* parent)
//    : QObject(parent) {
  PrinterController::PrinterController(VitalsService* vs, QObject* parent)
    : QObject(parent),
      m_vitalsService(vs)   // CRITICAL
{
    qDebug() << "[PC] VitalsService ptr:" << m_vitalsService;
      

    //VitalsService* vitalsService = new VitalsService(this);

    connect(&m_service, &PrinterService::printSuccess,
            this, &PrinterController::printCompleted);

    connect(&m_service, &PrinterService::printFailed,
            this, &PrinterController::printError);

    //connect(view, &PrintView::startPrintingRequested,
    //    this, &PrinterController::onPrintRequested);
}

void PrinterController::handlePrintRequest(const QString& filePath) {
    PrintJob job;
    job.filePath = filePath;
    job.printerIp = "192.168.1.100"; // configurable

    m_repo.saveJob(job);
    m_service.print(job);
}

void PrinterController::onThermalPrintRequested()
{
    qDebug() << "Printer Controller received thermal print request";

    if (!m_vitalsService)
    {
        qCritical() << "VitalsService is NULL → CRASH PREVENTED";
        return;
    }

    int sessionId = m_vitalsService->sessionId();

    if (sessionId <= 0)
    {
        qWarning() << "Invalid sessionId:" << sessionId;
        return;
    }

    qDebug() << "Printing session:" << sessionId;

    m_vitalsService->printResults(sessionId);
}
/*
void PrinterController::onThermalPrintRequested() {
    qDebug() << "Printer Controller received thermal print request from print view";
    // For testing, we can directly call the print logic here with dummy data, or we can emit a signal to start the process. 
    // For now, let's directly call the print logic with dummy data.
    VitalsService* vitalsService = new VitalsService(this);
    vitalsService->printResults(123); // Pass a valid session ID here
}
*/
void PrinterController::onPrintRequested() {
    qDebug() << "Controller received print request (SIMULATION)";

    // Create dummy data (same as your log)
    QMap<QString, QVariant> data;
    data["name"] = "Bhagyesh";
    data["age"] = 23;
    data["gender"] = "Male";
    data["temperature"] = 95.7;
    data["spo2"] = 0;
    data["pulse"] = 0;
    data["sys"] = 0;
    data["dia"] = 0;
    data["weight"] = 0;
    data["height"] = 0;

    QString pdf = generatePdfFromMap(data);

    handlePrintRequest(pdf);
}

QString PrinterController::generatePdfFromMap(const QMap<QString, QVariant>& data) {
    QString filePath = "/tmp/vitals_report.pdf";

    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));

    QPainter painter(&writer);

    painter.drawText(100,100,"Medical Report");
    painter.drawText(100,200,"Name: " + data["name"].toString());

    painter.end();

    qDebug() << "PDF Generated at:" << filePath;
    return filePath;
}

