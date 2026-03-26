#pragma once
#include <QObject>
#include <QImage>

class PrintServiceClient : public QObject {
    Q_OBJECT
public:
    explicit PrintServiceClient(QObject* parent=nullptr);
    void sendPrintJob(const QImage& img);

signals:
    void printDone(bool ok, const QString& msg);
};

