#include "printcontroller.h"
#include <QFile>

static QByteArray imageToRaster(const QImage& img)
{
    QImage mono = img.convertToFormat(QImage::Format_Mono);
    int w = mono.width();
    int h = mono.height();

    QByteArray data;
    data.append("\x1D\x76\x30\x00"); // GS v 0
    data.append(w / 8 & 0xFF);
    data.append((w / 8) >> 8);
    data.append(h & 0xFF);
    data.append(h >> 8);

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; x += 8) {
            uchar byte = 0;
            for (int b = 0; b < 8; ++b) {
                if (mono.pixelColor(x + b, y) == Qt::black)
                    byte |= (1 << (7 - b));
            }
            data.append(byte);
        }
    }
    return data;
}

bool PrinterController::printQR(const QImage& image, const QString& text)
{
    QFile printer("/dev/usb/lp0");
    if (!printer.open(QIODevice::WriteOnly))
        return false;

    QByteArray cmd;

    cmd += "\x1B\x40"; // Init
    cmd += "\x1B\x61\x01"; // Center align

    if (!text.isEmpty()) {
        cmd += text.toUtf8();
        cmd += "\n\n";
    }

    cmd += imageToRaster(image);
    cmd += "\n\n";
    cmd += "\x1D\x56\x00"; // Cut

    printer.write(cmd);
    printer.close();
    return true;
}

