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

    void setSessionId(int id);
    int sessionId() const;
    int patientId() const;

signals:
    void backRequested();
    void startThermalPrintingRequested(int sessionId);
    void startNetworkPrintingRequested(int sessionId);
    void exitRequested();   

private:

    int m_sessionId = -1;
    int m_patientId = -1;

    QLabel* statusLabel;

    QLabel* patientInfoLabel;

    QLabel* tempLabel;
    QLabel* spo2Label;
    QLabel* nibpLabel;
    QLabel* weightLabel;
    QLabel* heightLabel;
    QLabel* bmiLabel;
    QLabel* bmiAnalysisLabel;
    QLabel* bmrLabel;
    QLabel* bsaLabel;
    QLabel* vitalsLabel;
    QLabel* farVisionLabel;
    QLabel* nearVisionLabel;
    
};