
#include "printerservice.h"

#include <QTcpSocket>
#include <QFile>
#include <QDebug>

#include <QImage>
#include <QPainter>
#include <QFont>
#include <QRect>
#include <QProcess>

PrinterService::PrinterService(QObject* parent)
    : QObject(parent)
{
}
//

bool PrinterService::printReport(
    const QString& text)
{
    qDebug() << "PRINTREPORT 1";

    if (!createPGM(text))
    {
        qDebug() << "createPGM failed";
        return false;
    }

    qDebug() << "PRINTREPORT 2";

    if (!createPWG())
    {
        qDebug() << "createPWG failed";
        return false;
    }

    qDebug() << "PRINTREPORT 3";

    PrintJob job;

    job.printerIp = "192.168.45.167";
    job.port = 631;
    job.filePath = "/tmp/report.pwg";

    return print(job);
}

bool PrinterService::createPGM(
    const QString& text)
{
    const int W = 2480;
    const int H = 3508;

    QImage img(
        W,
        H,
        QImage::Format_Grayscale8);

    img.fill(255);

    QPainter p(&img);

    QFont font("Courier New");
    font.setPointSize(28);
    font.setBold(true);

    p.setFont(font);

    QFontMetrics fm(font);

    QRect textBounds =
        fm.boundingRect(
            QRect(0, 0, W - 400, H),
            Qt::TextWordWrap,
            text);

    QRect rect(
        (W - textBounds.width()) / 2,
        (H - textBounds.height()) / 2,
        textBounds.width(),
        textBounds.height());

    p.drawText(
        rect,
        Qt::TextWordWrap,
        text);

    /*QFont font;
    font.setPointSize(18);
    p.setFont(font);

    QRect rect(
        100,
        100,
        W - 200,
        H - 200);

    p.drawText(
        rect,
        Qt::TextWordWrap,
        text);
    */
    p.end();

    return img.save(
        "/tmp/report.pgm",
        "PGM");
}

bool PrinterService::createPWG()
{
    qDebug() << "PWG START";

    QProcess proc;

    qDebug() << "Launching pwg_writer";
    qDebug() << "Program: /opt/pwg_writer";
    qDebug() << "Input : /tmp/report.pgm";
    qDebug() << "Output: /tmp/report.pwg";

    proc.start(
        "/opt/pwg_writer",
        QStringList()
            << "/tmp/report.pgm"
            << "/tmp/report.pwg");

    proc.waitForFinished();

    qDebug() << "ExitStatus =" << proc.exitStatus();
    qDebug() << "ExitCode   =" << proc.exitCode();
    qDebug() << "Error      =" << proc.error();
    qDebug() << "ErrorString=" << proc.errorString();

    qDebug() << "STDOUT:";
    qDebug().noquote() << proc.readAllStandardOutput();

    qDebug() << "STDERR:";
    qDebug().noquote() << proc.readAllStandardError();

    return proc.exitStatus() == QProcess::NormalExit &&
           proc.exitCode() == 0;
}
static void appendUint16(QByteArray& b, quint16 v)
{
    b.append(char((v >> 8) & 0xFF));
    b.append(char(v & 0xFF));
}

static void appendUint32(QByteArray& b, quint32 v)
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

    appendUint16(ipp, name.toUtf8().size());
    ipp.append(name.toUtf8());

    appendUint16(ipp, value.toUtf8().size());
    ipp.append(value.toUtf8());
}

bool PrinterService::print(const PrintJob& job)
{
    QFile file(job.filePath);

    if (!file.open(QIODevice::ReadOnly))
    {
        //emit printFailed("Cannot open PWG");

        return false;
    }

    QByteArray pwg = file.readAll();

    file.close();

    qDebug() << "Loaded file:" << pwg.size();

    // =====================================================
    // BUILD IPP
    // =====================================================

    QByteArray ipp;

    // IPP 2.0
    ipp.append(char(0x02));
    ipp.append(char(0x00));

    // Print-Job
    ipp.append(char(0x00));
    ipp.append(char(0x02));

    // Request ID
    appendUint32(ipp, 1);

    // operation attributes
    ipp.append(char(0x01));

    QString uri =
        QString("ipp://%1:631/ipp/print")
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
        0x49,
        "document-format",
        "image/pwg-raster");

    // IMPORTANT
    addIPPString(
        ipp,
        0x42,
        "job-name",
        "Vitals Report");

    // end attributes
    ipp.append(char(0x03));

    // append PWG
    ipp.append(pwg);

    // =====================================================
    // HTTP
    // =====================================================

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
        QString("Content-Length: %1\r\n")
        .arg(ipp.size())
        .toUtf8();

    http +=
        "Connection: close\r\n";

    http +=
        "\r\n";

    // =====================================================
    // CONNECT
    // =====================================================

    QTcpSocket socket;

    socket.connectToHost(job.printerIp, 631);

    if (!socket.waitForConnected(5000))
    {
        //emit printFailed("Connect failed");

        return false;
    }

    qDebug() << "Connected to printer";

    // =====================================================
    // SEND HTTP
    // =====================================================

    socket.write(http);

    if (!socket.waitForBytesWritten(5000))
    {
        //emit printFailed("HTTP send failed");

        return false;
    }

    // =====================================================
    // SEND IPP
    // =====================================================

    qint64 total = 0;

    while (total < ipp.size())
    {
        qint64 n =
            socket.write(
                ipp.constData() + total,
                ipp.size() - total);

        if (n <= 0)
        {
            //emit printFailed("IPP write failed");

            return false;
        }

        total += n;

        socket.waitForBytesWritten(5000);
    }

    qDebug() << "All IPP data sent";

    // =====================================================
    // RECEIVE RESPONSE
    // =====================================================

    if (!socket.waitForReadyRead(10000))
    {
        //emit printFailed("No printer response");

        return false;
    }

    QByteArray response =
        socket.readAll();

    qDebug()
        << "PRINTER RESPONSE:\n"
        << response;

    if (!response.contains("200 OK"))
    {
        //emit printFailed("IPP failed");

        return false;
    }

    qDebug() << "BEFORE SIGNAL";

    // emit printSuccess(); //crashes here - as no signal connected to this slot

    qDebug() << "AFTER SIGNAL";

    return true;

    
}
