#include "controller/printercontroller.h"

#include "view/printview.h"
#include <QDebug>
#include "service/vitalsservice.h"
#include "storage/vitalsrepository.h"
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QMap>
#include <QVariant>

#include <QFile>
#include <QImage>
#include <QPainter>
#include <QFont>
#include <QColor>
#include <QIODevice>

#include "service/printerservice.h"

PrinterController::PrinterController(VitalsService* vs, 
    VitalsRepository* 
    vitalRepo,QObject* parent)
    : QObject(parent),
      m_repo(vitalRepo),
      m_vitalsService(vs)   // CRITICAL
      
{
    //qDebug() << "[PC] VitalsService ptr:" << m_vitalsService;
      

    //VitalsService* vitalsService = new VitalsService(this);

    //connect(&m_service, &PrinterService::printSuccess,
    //        this, &PrinterController::printCompleted);

    //connect(&m_service, &PrinterService::printFailed,
    //        this, &PrinterController::printError);

    //connect(view, &PrintView::startPrintingRequested,
    //    this, &PrinterController::onPrintRequested);
}

void PrinterController::handlePrintRequest(const QString& filePath) {
    PrintJob job;
    job.filePath = filePath;
    job.printerIp = "192.168.1.100"; // configurable

    //m_repo.saveJob(job);
    //m_service.print(job);
}

void PrinterController::onNetworkPrintRequested(int sessionId)
{
    qDebug()
        << "Printing historical session:"
        << sessionId;

    QVariantMap data =
        m_repo->getLatestVitals(sessionId);

    QString text =
        m_vitalsService->buildPrintText(
            sessionId,
            data);

    m_printerService->printReport(text);
}
/*
void PrinterController::onThermalPrintRequested(int sessionId)
{
    qDebug()
        << "Printing historical session:"
        << sessionId;

    QVariantMap data =
        m_repo->getLatestVitals(sessionId);

    QString text =
        m_vitalsService->buildPrintText(
            sessionId,
            data);

    m_printerService->printReport(text);
}
*/

void PrinterController::onThermalPrintRequested(int sessionId)
{
        qDebug()
        << "Printing old session:"
        << sessionId;

    qDebug() << "Printer Controller Printing session:" << sessionId;

    if (sessionId <= 0)
    {
        qDebug() << "Invalid session!";
        return;
    }

    QVariantMap data = m_repo->getLatestVitals(sessionId);

    qDebug() << "PRINT DATA MAP:" << data;

    if (data.isEmpty())
    {
        qDebug() << "No data found for session!";
        return;
    }

        QString text =
        m_vitalsService->buildPrintText(
            sessionId,
            data);

        qDebug() << "PRINT TEXT:\n" << text;

        m_vitalsService->printResults(sessionId, data);
        //bool ok =
        //m_printerService->printReport(text);

    //qDebug() << "Print result =" << ok;
}

/*
void PrinterController::onNetworkPrintRequested()
{
    int sessionId =
        m_printView->sessionId();

    QVariantMap data =
        m_repo->getLatestVitals(sessionId);

    QString text =
        m_vitalsService->buildPrintText(
            sessionId,
            data);

    m_printerService->printReport(text);
}
*/
/*
void PrinterController::onNetworkPrintRequested()
{
   
   
    int sessionId = m_vitalsService->sessionId();

        QVariantMap data =
        m_repo->getLatestVitals(sessionId);

    qDebug() << "STEP 1";

        QString text =
            m_vitalsService->buildPrintText(
                sessionId,
                data);

        qDebug() << "STEP 2";

        bool ok =
            m_printerService->printReport(text);

        qDebug()
            << "STEP 3 result="
            << ok;


    //QVariantMap data =
    //    m_repo->getLatestVitals(sessionId);

    //QString printText =
    //    m_vitalsService->buildPrintText(
    //        sessionId,
    //        data);

    //m_printerService->printReport(
    //    printText);

}
*/
//
/*
void PrinterController::onNetworkPrintRequested()
{
    qDebug() << "Controller received network print request";

    int sessionId = m_vitalsService->sessionId();

    qDebug() << "Printer Controller Network Printing Session:" << sessionId;

    if (sessionId <= 0)
    {
        qDebug() << "Invalid session!";
        return;
    }

    QVariantMap data =
        m_repo->getLatestVitals(sessionId);

    qDebug() << "PRINT DATA MAP:" << data;

    if (data.isEmpty())
    {
        qDebug() << "No data found for session!";
        return;
    }
    //Create printer service instance here or inject via constructor?
    PrinterService* printerService =
    new PrinterService(this);

    m_printerService = printerService;
    // ----------------------------------------------------
    // BUILD PRINT TEXT
    // ----------------------------------------------------

    QString text =
        m_vitalsService->buildPrintText(
            sessionId,
            data);

    qDebug() << "PRINT TEXT:\n" << text;

    // ----------------------------------------------------
    // CREATE IMAGE
    // ----------------------------------------------------

    const int W = 2481;
    const int H = 3508;

    QImage img(
        W,
        H,
        QImage::Format_Grayscale8);

    img.fill(255);

    QPainter p(&img);

    QFont font;

    font.setPointSize(18);

    p.setFont(font);

    // IMPORTANT
    p.setPen(QColor(80,80,80));

    QRect rect(
        120,
        120,
        W - 240,
        H - 240);

    p.drawText(
        rect,
        Qt::TextWordWrap,
        text);

    p.end();

    // ----------------------------------------------------
    // LOAD KNOWN-GOOD HEADER
    // ----------------------------------------------------

    QFile hdr("/opt/header.bin");

    if (!hdr.open(QIODevice::ReadOnly))
    {
        qDebug() << "Cannot open header.bin";
        return;
    }

    QByteArray header =
        hdr.readAll();

    hdr.close();

    // ----------------------------------------------------
    // CREATE PWG
    // ----------------------------------------------------

    QString pwgFile =
        "/tmp/report.pwg";

    QFile out(pwgFile);

    if (!out.open(QIODevice::WriteOnly))
    {
        qDebug() << "Cannot create PWG";
        return;
    }

    out.write(header);

    for (int y = 0; y < H; y++)
    {
        const uchar* line =
            img.constScanLine(y);

        QByteArray row(
            reinterpret_cast<const char*>(line),
            W);

        // IMPORTANT
        // slightly lighten
        for (int i = 0; i < row.size(); i++)
        {
            uchar v =
                static_cast<uchar>(row[i]);

            if (v < 120)
                row[i] = char(120);
        }

        out.write(row);
    }

    out.close();

    qDebug() << "PWG GENERATED:" << pwgFile;

    // ----------------------------------------------------
    // SEND TO NETWORK PRINTER
    // ----------------------------------------------------

    PrintJob job;

    job.printerIp = "192.168.45.167";
    job.port = 631;
    job.filePath = pwgFile;

    bool ok =
        m_printerService->print(job);

    if (ok)
        qDebug() << "Network print success";
    else
        qDebug() << "Network print failed";
}
    */
/*working on network print flow 
void PrinterController::onPrintRequested() {
    qDebug() << "Controller received network print request from print view";

    int sessionId = m_vitalsService->sessionId();

    qDebug() << "Network Printing Session:" << sessionId;

    if (sessionId <= 0)
    {
        qDebug() << "Invalid session!";
        return;
    }

    QVariantMap data = m_repo->getLatestVitals(sessionId);

    qDebug() << "PRINT DATA MAP:" << data;

    if (data.isEmpty())
    {
        qDebug() << "No data found for session!";
        return;
    }
    //network print flow - generate PDF and send to printer
    
}
*/
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

