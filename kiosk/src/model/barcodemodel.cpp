
#include "barcodemodel.h"

BarcodeModel::BarcodeModel(QObject* parent)
    : QObject(parent)
{
}

void BarcodeModel::setBarcode(const QString& text, const QString& format)
{
    if (text == m_text && format == m_format)
        return;

    m_text = text;
    m_format = format;
    emit barcodeChanged();
}


