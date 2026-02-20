
#pragma once
#include <QObject>
#include <QImage>

class BarcodeScanner : public QObject
{
    Q_OBJECT
public:
    explicit BarcodeScanner(QObject* parent = nullptr);

public slots:
    void onFrame(const QImage& gray);

signals:
    void barcodeDetected(const QString& text,
                         const QString& format);
};

