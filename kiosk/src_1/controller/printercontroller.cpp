// printercontroller.cpp

#include "controller/printercontroller.h"

#include "view/printview.h"

#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QMap>
#include <QVariant>
#include <QFile>
#include <QImage>
#include <QFont>
#include <QColor>
#include <QIODevice>

#include <cstring>
#include <stdint.h>

#include "service/vitalsservice.h"
#include "storage/vitalsrepository.h"
#include "service/printerservice.h"

#pragma pack(push,1)

struct PWGHeader
{
    char     sync[4];

    uint32_t width;
    uint32_t height;

    uint32_t dpiX;
    uint32_t dpiY;

    uint32_t bitsPerPixel;

    uint32_t colorSpace;

    uint32_t bytesPerLine;

    char reserved[64];
};

#pragma pack(pop)

PrinterController::PrinterController(
    VitalsService* vs,
    VitalsRepository* vitalRepo,
    QObject* parent)
    : QObject(parent),
      m_vitalsService(vs),
      m_repo(vitalRepo)
{
}

void PrinterController::onThermalPrintRequested()
{
    int sessionId =
        m_vitalsService->sessionId();

    qDebug()
        << "Printing session:"
        << sessionId;

    if (sessionId <= 0)
    {
        qDebug() << "Invalid session!";
        return;
    }

    QVariantMap data =
        m_repo->getLatestVitals(sessionId);

    qDebug()
        << "PRINT DATA MAP:"
        << data;

    if (data.isEmpty())
    {
        qDebug()
            << "No data found for session!";
        return;
    }

    m_vitalsService->printResults(
        sessionId,
        data);
}
void PrinterController::onNetworkPrintRequested()
{
    qDebug() << "Controller received network print request";

    int sessionId =
        m_vitalsService->sessionId();

    qDebug() << "Network Printing Session:"
             << sessionId;

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
        qDebug() << "No data found!";
        return;
    }

    // =====================================================
    // BUILD TEXT
    // =====================================================

    QString text =
        m_vitalsService->buildPrintText(
            sessionId,
            data);

    qDebug() << "PRINT TEXT:\n" << text;

    // =====================================================
    // CREATE IMAGE
    // =====================================================

    const int W = 2481;
    const int H = 3508;

    QImage img(
        W,
        H,
        QImage::Format_Grayscale8);

    img.fill(255);

    QPainter p(&img);

    QFont font;

    font.setPointSize(22);

    p.setFont(font);

    // PURE BLACK
    p.setPen(Qt::black);

    QRect rect(
        150,
        150,
        W - 300,
        H - 300);

    p.drawText(
        rect,
        Qt::TextWordWrap,
        text);

    p.end();

    // =====================================================
    // LOAD KNOWN GOOD HEADER
    // =====================================================

    QFile hdr("/opt/header.bin");

    if (!hdr.open(QIODevice::ReadOnly))
    {
        qDebug() << "Cannot open /opt/header.bin";
        return;
    }

    QByteArray header =
        hdr.readAll();

    hdr.close();

    qDebug() << "HEADER SIZE:"
             << header.size();

    // =====================================================
    // CREATE PWG
    // =====================================================

    QString pwgFile =
        "/tmp/report.pwg";

    QFile out(pwgFile);

    if (!out.open(QIODevice::WriteOnly))
    {
        qDebug() << "Cannot create PWG";
        return;
    }

    // exact working header
    out.write(header);

    // IMPORTANT:
    // WRITE RAW SCANLINES DIRECTLY
    // DO NOT MODIFY ROW DATA

    for (int y = 0; y < H; y++)
    {
        out.write(
            reinterpret_cast<const char*>(
                img.constScanLine(y)),
            W);
    }

    out.close();

    qDebug() << "PWG GENERATED:"
             << pwgFile;

    // =====================================================
    // SEND TO PRINTER
    // =====================================================

    PrinterService* printerService =
        new PrinterService(this);

    PrintJob job;

    job.printerIp = "192.168.45.167";
    job.port      = 631;
    job.filePath  = pwgFile;

    bool ok =
        printerService->print(job);

    if (ok)
        qDebug() << "Network print success";
    else
        qDebug() << "Network print failed";
}
/*
void PrinterController::onNetworkPrintRequested()
{
    qDebug()
        << "Controller received network print request";

    int sessionId =
        m_vitalsService->sessionId();

    qDebug()
        << "Network Printing Session:"
        << sessionId;

    if (sessionId <= 0)
    {
        qDebug() << "Invalid session!";
        return;
    }

    QVariantMap data =
        m_repo->getLatestVitals(sessionId);

    qDebug()
        << "PRINT DATA MAP:"
        << data;

    if (data.isEmpty())
    {
        qDebug()
            << "No data found for session!";
        return;
    }

    // =====================================================
    // CREATE PRINTER SERVICE
    // =====================================================

    PrinterService* printerService =
        new PrinterService(this);

    m_printerService =
        printerService;

    // =====================================================
    // BUILD PRINT TEXT
    // =====================================================

    QString text =
        m_vitalsService->buildPrintText(
            sessionId,
            data);

    qDebug()
        << "PRINT TEXT:\n"
        << text;

    // =====================================================
    // PAGE GEOMETRY
    // =====================================================

    const int W = 2481;
    const int H = 3508;

    // =====================================================
    // CREATE IMAGE
    // =====================================================

    QImage img(
        W,
        H,
        QImage::Format_Grayscale8);

    img.fill(255);

    QPainter p(&img);

    QFont font;

    font.setPointSize(20);

    p.setFont(font);

    p.setPen(Qt::black);

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

    // =====================================================
    // CREATE PWG FILE
    // =====================================================

    QString pwgFile =
        "/tmp/report.pwg";

    QFile out(pwgFile);

    if (!out.open(QIODevice::WriteOnly))
    {
        qDebug()
            << "Cannot create PWG";

        return;
    }

    // =====================================================
    // BUILD PWG HEADER
    // =====================================================

    PWGHeader h;

    memset(&h, 0, sizeof(h));

    memcpy(h.sync, "RaS2", 4);

    h.width  = W;
    h.height = H;

    h.dpiX = 300;
    h.dpiY = 300;

    h.bitsPerPixel = 8;

    // grayscale
    h.colorSpace = 18;

    h.bytesPerLine = W;

    // =====================================================
    // WRITE PWG HEADER
    // =====================================================

    out.write(
        reinterpret_cast<char*>(&h),
        sizeof(h));

    // =====================================================
    // WRITE RAW RASTER ROWS
    // =====================================================

    for (int y = 0; y < H; y++)
    {
        out.write(
            reinterpret_cast<const char*>(
                img.constScanLine(y)),
            W);
    }

    out.close();

    qDebug()
        << "PWG GENERATED:"
        << pwgFile;

    // =====================================================
    // SEND TO NETWORK PRINTER
    // =====================================================

    PrintJob job;

    job.printerIp =
        "192.168.45.167";

    job.port = 631;

    job.filePath =
        pwgFile;

    bool ok =
        m_printerService->print(job);

    if (ok)
    {
        qDebug()
            << "Network print success";
    }
    else
    {
        qDebug()
            << "Network print failed";
    }
}
*/
QString PrinterController::generatePdfFromMap(
    const QMap<QString, QVariant>& data)
{
    QString filePath =
        "/tmp/vitals_report.pdf";

    QPdfWriter writer(filePath);

    writer.setPageSize(
        QPageSize(QPageSize::A4));

    QPainter painter(&writer);

    painter.drawText(
        100,
        100,
        "Medical Report");

    painter.drawText(
        100,
        200,
        "Name: " +
        data["name"].toString());

    painter.end();

    qDebug()
        << "PDF Generated at:"
        << filePath;

    return filePath;
}