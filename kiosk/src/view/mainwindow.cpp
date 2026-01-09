#include "mainwindow.h"
#include <QPainter>
#include <QFont>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    resize(640, 480);
}

void MainWindow::updateFrame(const QImage& img)
{
    m_frame = img;
    update();   // trigger repaint
}

void MainWindow::updateBarcode(const QString& text, const QString& format)
{
    m_text = text;
    m_format = format;
    update();
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    // Draw camera frame
    if (!m_frame.isNull()) {
        p.drawImage(rect(), m_frame);
    }

    // Draw overlay if barcode exists
    if (!m_text.isEmpty()) {
        p.setPen(Qt::yellow);
        p.setBrush(QColor(0, 0, 0, 160));
        p.drawRect(10, height() - 70, width() - 20, 60);

        p.setPen(Qt::white);
        p.setFont(QFont("Sans", 14, QFont::Bold));

        p.drawText(
            QRect(20, height() - 65, width() - 40, 50),
            Qt::AlignLeft | Qt::AlignVCenter,
            QString("%1\n%2").arg(m_format, m_text)
        );
    }
}



