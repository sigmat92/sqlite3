
#pragma once
#include <QString>

struct PrintJob {
    QString filePath;
    QString printerIp;
    int port = 9100;
};