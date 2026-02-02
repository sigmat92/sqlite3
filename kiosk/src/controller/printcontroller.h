#pragma once
#include <QImage>
#include <QString>

class PrinterController {
public:
    static bool printQR(const QImage& image, const QString& text = "");
};

