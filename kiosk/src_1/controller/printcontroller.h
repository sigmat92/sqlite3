#pragma once
#include <QObject>
#include <QImage>

class PrintServiceClient;

class PrintController : public QObject {
    Q_OBJECT
public:
    explicit PrintController(QObject* parent=nullptr);
    void printQR(const QImage& img);

signals:
    void printResult(bool ok, const QString& msg);

private:
    PrintServiceClient* client;
};

