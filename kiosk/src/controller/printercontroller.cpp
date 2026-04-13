#include "controller/printercontroller.h"
#include "view/printview.h"
#include <QDebug>

#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QMap>
#include <QVariant>

PrinterController::PrinterController(QObject* parent)
    : QObject(parent) {

    //PrintView* view = new PrintView;
    
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
/*
QString generatePdfFromMap(const QMap<QString, QVariant>& data) {
    QString filePath = "/tmp/vitals_report.pdf";

    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));

    QPainter painter(&writer);

    painter.drawText(100,100,"Medical Report");

    painter.drawText(100,200,"Name: " + data["name"].toString());
    painter.drawText(100,250,"Age: " + QString::number(data["age"].toInt()));
    painter.drawText(100,300,"Gender: " + data["gender"].toString());
    painter.drawText(100,350,"Temp: " + QString::number(data["temperature"].toDouble()));
    painter.drawText(100,400,"SpO2: " + QString::number(data["spo2"].toInt()));
    painter.drawText(100,450,"Pulse: " + QString::number(data["pulse"].toInt()));

    painter.end();

    qDebug() << "PDF Generated at:" << filePath;
    return filePath;
}
*/
