#pragma once
#include <QMainWindow>
#include <QImage>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

public slots:
    void updateFrame(const QImage& img);
    void updateBarcode(const QString& text, const QString& format);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    QImage  m_frame;
    QString m_text;
    QString m_format;
};



