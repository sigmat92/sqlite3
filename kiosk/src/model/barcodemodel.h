
#pragma once
#include <QObject>
#include <QString>

class BarcodeModel : public QObject
{
    Q_OBJECT
public:
    explicit BarcodeModel(QObject* parent = nullptr);

    QString text() const { return m_text; }
    QString format() const { return m_format; }

public slots:
    void setBarcode(const QString& text, const QString& format);

signals:
    void barcodeChanged();

private:
    QString m_text;
    QString m_format;
};


/*
#pragma once
#include <QObject>
#include <QString>

class BarcodeModel : public QObject
{
    Q_OBJECT
public:
    explicit BarcodeModel(QObject* parent = nullptr);

    QString text() const { return m_text; }
    QString format() const { return m_format; }

public slots:
    void setBarcode(const QString& text, const QString& format);

signals:
    void barcodeChanged();

private:
    QString m_text;
    QString m_format;
};
*/
