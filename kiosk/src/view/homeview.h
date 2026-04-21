#pragma once

#include "baseview.h"
#include "metriccard.h"

#include <QLineEdit>
#include <QRadioButton>
#include <QLabel>

class HomeView : public BaseView
{
    Q_OBJECT

public:
    explicit HomeView(QWidget *parent = nullptr);

    QString patientName() const;
    QString patientAge() const;
    QString patientMobile() const;
    QString patientGender() const;

    void lockPatientFields();
    void unlockPatientFields();
    void clearPatientFields();

    void showError(const QString &msg);

    void setCurrentSessionId(int id);

public slots:

    void setTemperatureBusy(bool busy);
    void setSpO2Busy(bool busy);
    void setNIBPBusy(bool busy);
    void setHeightBusy(bool busy);
    void setWeightBusy(bool busy);

    void setTemperatureText(const QString &text);
    void setNIBPText(const QString &text);
    void setHeightText(const QString &text);
    void setWeightText(const QString &text);
    void setSpo2Text(const QString &text);
    
    void onVitalsUpdated(int spo2,int pulse);

signals:
    void startSpo2Requested();
    void startTemperatureRequested();
    void startNIBPRequested();
    void startHeightRequested();
    void startWeightRequested();
    //void visionTestRequested(int sessionId);
    void visionTestRequested();
    void settingsRequested();

    void resetSessionRequested();  
    void startPrintingRequested(int sessionId); 
    
    void startSessionRequested(QString name,
                               int age,
                               QString mobile,
                               QString gender);
    void newSessionRequested();

private:

    QLabel *statusLabel;

    QLineEdit *nameEdit;
    QLineEdit *ageEdit;
    QLineEdit *mobileEdit;

    QRadioButton *maleBtn;
    QRadioButton *femaleBtn;

    MetricCard* temperatureCard = nullptr;
    MetricCard* spo2Card = nullptr;
    MetricCard* nibpCard = nullptr;
    MetricCard* weightCard = nullptr;
    MetricCard* heightCard = nullptr;
    MetricCard* visionTestCard = nullptr;

    QLabel *bmiLabel;
    QLabel *bmiAnalysisLabel;
    QLabel *bmrLabel;
    QLabel *bsaLabel;
    QLabel *farVisionLabel;
    QLabel *nearVisionLabel;

    bool sessionStarted = false;
    int currentSessionId = -1;
};
