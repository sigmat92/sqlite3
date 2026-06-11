#pragma once
#include <QImage>
#include <QString>

class QRGenerator
{
public:
    static QImage generate(const QString& text, int size = 256);
};

