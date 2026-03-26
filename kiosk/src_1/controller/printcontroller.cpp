#include "printcontroller.h"
#include "../model/printserviceclient.h"

PrintController::PrintController(QObject* parent)
    : QObject(parent)
{
    client = new PrintServiceClient(this);
    connect(client, &PrintServiceClient::printDone,
            this, &PrintController::printResult);
}

void PrintController::printQR(const QImage& img)
{
    client->sendPrintJob(img);
}

