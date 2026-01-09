
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

/*
#pragma once
#include <QObject>
#include <QImage>
#include "../model/barcodemodel.h"

class BarcodeScanner : public QObject
{
    Q_OBJECT
public:
    explicit BarcodeScanner(BarcodeModel* model, QObject* parent = nullptr);

public slots:
    void onGrayFrame(const QImage& gray);

private:
    BarcodeModel* m_model;
};
*/
