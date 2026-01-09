#include "barcodescanner.h"

//#include <ZXing/ReadBarcode.h>
//#include <ZXing/ZXVersion.h>
#include <ReadBarcode.h>
#include <ZXVersion.h>

BarcodeScanner::BarcodeScanner(QObject* parent)
    : QObject(parent)
{
}

void BarcodeScanner::onFrame(const QImage& gray)
{
    ZXing::ImageView img(gray.bits(),
                         gray.width(),
                         gray.height(),
                         ZXing::ImageFormat::Lum);

    auto result = ZXing::ReadBarcode(img);
    if (!result.isValid())
        return;

    emit barcodeDetected(
        QString::fromStdString(result.text()),
        QString::fromStdString(ZXing::ToString(result.format()))
    );
}

/*
#include "barcodescanner.h"
#include <ZXing/ReadBarcode.h>
#include <ZXing/ImageView.h>

BarcodeScanner::BarcodeScanner(BarcodeModel* model, QObject* parent)
    : QObject(parent), m_model(model)
{
}

void BarcodeScanner::onGrayFrame(const QImage& gray)
{
    ZXing::ImageView view(
        gray.bits(),
        gray.width(),
        gray.height(),
        ZXing::ImageFormat::Lum
    );

    auto result = ZXing::ReadBarcode(view);
    if (result.isValid()) {
        m_model->setBarcode(
            QString::fromStdString(result.text()),
            QString::fromStdString(ZXing::ToString(result.format()))
        );
    }
}
*/
