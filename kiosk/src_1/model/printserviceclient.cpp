#include "printserviceclient.h"
#include "../service/protocol.h"
#include <QTcpSocket>
#include <QBuffer>
#include <QUuid>

PrintServiceClient::PrintServiceClient(QObject* parent)
    : QObject(parent)
{}

void PrintServiceClient::sendPrintJob(const QImage& img)
{
    QTcpSocket sock;
    sock.connectToHost("127.0.0.1", 9100);

    if (!sock.waitForConnected(1000)) {
        emit printDone(false, "Print service not running");
        return;
    }

    QImage mono = img.convertToFormat(QImage::Format_Mono);

    QByteArray payload;
    QBuffer buf(&payload);
    buf.open(QIODevice::WriteOnly);
    mono.save(&buf, "PBM");

    //sock.write("PRINT\n");
    //
    // sock.write(payload);
    
    QString jobId = QUuid::createUuid().toString(QUuid::Id128);

    sock.write(QString("PRINT %1 %2\n")
           .arg(jobId)
           .arg(payload.size())
           
           .toUtf8());

    sock.write(payload);

    sock.waitForBytesWritten();

    sock.waitForReadyRead();
    QString resp = sock.readAll();

    emit printDone(resp.startsWith("OK"), resp.trimmed());
}

