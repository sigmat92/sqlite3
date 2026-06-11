#include "qrgenerator.h"
//#include <Writer.h>
#include <QPixmap>
#include <MultiFormatWriter.h>
#include <BarcodeFormat.h>
#include <BitMatrix.h>

QImage QRGenerator::generate(const QString& text, int size)
{
	ZXing::MultiFormatWriter writer(ZXing::BarcodeFormat::QRCode);
    	writer.setMargin(2);

	ZXing::BitMatrix matrix = writer.encode(
        text.toStdString(),
        300,
        300
    );

    QImage img(matrix.width(), matrix.height(), QImage::Format_RGB32);
    img.fill(Qt::white);

    for (int y = 0; y < matrix.height(); ++y) {
        for (int x = 0; x < matrix.width(); ++x) {
            if (matrix.get(x, y))
                img.setPixel(x, y, qRgb(0, 0, 0));
        }
    }
//label->setPixmap(QPixmap::fromImage(img));
    return img;
}

