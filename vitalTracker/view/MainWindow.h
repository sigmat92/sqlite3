#pragma once
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include "WaveformWidget.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setECG(double val);
    void setRESP(double val);
    void setSPO2(double val);
    void setBP(int sys, int dia);
    void setFooterText(const QString &text);

private slots:
    void updateTime();

public:
    WaveformWidget *ecgWidget;
    WaveformWidget *respWidget;
    WaveformWidget *spo2Widget;
    WaveformWidget *bpWidget;

private:
    // Header
    QLabel *bedLabel;
    QLabel *timeLabel;

    // Vitals
    QLabel *ecgLabel;
    QLabel *respLabel;
    QLabel *spo2Label;
    QLabel *bpLabel;

    // Footer
    QLabel *footerLabel;

    QTimer *timer;
};

