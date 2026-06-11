#include "printerservice.h"

#include <QTcpSocket>
#include <QFile>
#include <QDebug>

PrinterService::PrinterService(QObject* parent)
    : QObject(parent)
{
}

// =====================================================
// HELPERS
// =====================================================

static void appendUint16(
    QByteArray& b,
    quint16 v)
{
    b.append(char((v >> 8) & 0xFF));
    b.append(char(v & 0xFF));
}

static void appendUint32(
    QByteArray& b,
    quint32 v)
{
    b.append(char((v >> 24) & 0xFF));
    b.append(char((v >> 16) & 0xFF));
    b.append(char((v >> 8) & 0xFF));
    b.append(char(v & 0xFF));
}

static void addIPPString(
    QByteArray& ipp,
    quint8 tag,
    const QString& name,
    const QString& value)
{
    ipp.append(char(tag));

    appendUint16(
        ipp,
        name.toUtf8().size());

    ipp.append(name.toUtf8());

    appendUint16(
        ipp,
        value.toUtf8().size());

    ipp.append(value.toUtf8());
}

// =====================================================
// PRINT
// =====================================================

bool PrinterService::print(
    const PrintJob& job)
{
    // =================================================
    // LOAD PWG
    // =================================================

    QFile file(job.filePath);

    if (!file.open(QIODevice::ReadOnly))
    {
        emit printFailed(
            "Cannot open PWG");

        return false;
    }

    QByteArray pwg =
        file.readAll();

    file.close();

    qDebug()
        << "Loaded file:"
        << pwg.size();

    // =================================================
    // BUILD IPP
    // =================================================

    QByteArray ipp;

    // IPP VERSION 2.0
    ipp.append(char(0x02));
    ipp.append(char(0x00));

    // Print-Job
    ipp.append(char(0x00));
    ipp.append(char(0x02));

    // Request ID
    appendUint32(ipp, 1);

    // operation-attributes-tag
    ipp.append(char(0x01));

    QString uri =
        QString(
            "ipp://%1:631/ipp/print")
        .arg(job.printerIp);

    addIPPString(
        ipp,
        0x47,
        "attributes-charset",
        "utf-8");

    addIPPString(
        ipp,
        0x48,
        "attributes-natural-language",
        "en");

    addIPPString(
        ipp,
        0x45,
        "printer-uri",
        uri);

    addIPPString(
        ipp,
        0x42,
        "requesting-user-name",
        "carenest");

    addIPPString(
        ipp,
        0x42,
        "job-name",
        "Vitals Report");

    addIPPString(
        ipp,
        0x49,
        "document-format",
        "image/pwg-raster");

    // end-of-attributes-tag
    ipp.append(char(0x03));

    // append PWG payload
    ipp.append(pwg);

    // =================================================
    // BUILD HTTP
    // =================================================

    QByteArray http;

    http +=
        "POST /ipp/print HTTP/1.1\r\n";

    http +=
        QString("Host: %1\r\n")
        .arg(job.printerIp)
        .toUtf8();

    http +=
        "Content-Type: application/ipp\r\n";

    http +=
        QString(
            "Content-Length: %1\r\n")
        .arg(ipp.size())
        .toUtf8();

    http +=
        "Connection: close\r\n";

    http +=
        "\r\n";

    // =================================================
    // CONNECT
    // =================================================

    QTcpSocket socket;

    socket.connectToHost(
        job.printerIp,
        631);

    if (!socket.waitForConnected(5000))
    {
        emit printFailed(
            "Connect failed");

        return false;
    }

    qDebug()
        << "Connected to printer";

    // =================================================
    // SEND HTTP HEADER
    // =================================================

    socket.write(http);

    if (!socket.waitForBytesWritten(5000))
    {
        emit printFailed(
            "HTTP send failed");

        return false;
    }

    // =================================================
    // SEND IPP PAYLOAD
    // =================================================

    qint64 total = 0;

    while (total < ipp.size())
    {
        qint64 n =
            socket.write(
                ipp.constData() + total,
                ipp.size() - total);

        if (n <= 0)
        {
            emit printFailed(
                "IPP write failed");

            return false;
        }

        total += n;

        if (!socket.waitForBytesWritten(5000))
        {
            emit printFailed(
                "Socket write timeout");

            return false;
        }
    }

    qDebug()
        << "All IPP data sent";

    // IMPORTANT
    socket.flush();

    socket.waitForBytesWritten(5000);

    socket.disconnectFromHost();

    // =================================================
    // OPTIONAL PRINTER RESPONSE
    // =================================================

    if (socket.waitForReadyRead(3000))
    {
        QByteArray response =
            socket.readAll();

        qDebug()
            << "PRINTER RESPONSE:\n"
            << response;

        if (!response.contains("200 OK"))
        {
            emit printFailed(
                "IPP failed");

            return false;
        }
    }
    else
    {
        qDebug()
            << "No printer response "
            << "(printer may still print normally)";
    }

    // =================================================
    // SUCCESS
    // =================================================

    emit printSuccess();

    return true;
}