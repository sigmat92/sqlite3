#include "printerservice.h"
#include <QTcpSocket>
#include <QFile>

PrinterService::PrinterService(QObject* parent)
    : QObject(parent) {}

bool PrinterService::print(const PrintJob& job) {
    QTcpSocket socket;

    socket.connectToHost(job.printerIp, job.port);
    if (!socket.waitForConnected(3000)) {
        emit printFailed("Connection failed");
        return false;
    }

    QFile file(job.filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        emit printFailed("File open failed");
        return false;
    }

    while (!file.atEnd()) {
        QByteArray chunk = file.read(1024);
        socket.write(chunk);
        if (!socket.waitForBytesWritten()) {
            emit printFailed("Write failed");
            return false;
        }
    }

    socket.disconnectFromHost();

    emit printSuccess();
    return true;
}