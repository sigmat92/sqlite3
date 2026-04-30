#pragma once
#include "baseview.h"
#include <QWidget>
#include <QVariantMap>

class QLabel;

class PrintView : public BaseView
{
    Q_OBJECT

public:
    explicit PrintView(QWidget* parent = nullptr);

    void setData(const QVariantMap& data);

signals:
    void backRequested();
    void startPrintingRequested();
    void exitRequested();   

private:

    QLabel* statusLabel;

    QLabel* patientInfoLabel;

    QLabel* tempLabel;
    QLabel* spo2Label;
    QLabel* nibpLabel;
    QLabel* weightLabel;
    QLabel* heightLabel;
    QLabel* bmiLabel;
    QLabel* vitalsLabel;
};