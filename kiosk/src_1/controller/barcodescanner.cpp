#include "barcodescanner.h"

#include <ReadBarcode.h>
//#include <ZXVersion.h>

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
	//QString::fromStdWString(result.text()),
        QString::fromStdString(ZXing::ToString(result.format()))
    );
}


