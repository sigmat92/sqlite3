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

public slots:
    void setTemperatureBusy(bool busy);
    void setTemperatureText(const QString &text);
    void onVitalsUpdated(int spo2,int pulse);

signals:
    void startSpo2Requested();
    void startTemperatureRequested();
    void startNIBPRequested();
    void startHeightRequested();
    void startWeightRequested();
    void visionTestRequested();
    void startPrintingRequested();
    void settingsRequested();

    void resetSessionRequested();   
    
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

    MetricCard *spo2Card = nullptr;
    MetricCard *temperatureCard = nullptr;

    QLabel *bmiLabel;
    QLabel *bmiAnalysisLabel;
    QLabel *bmrLabel;
    QLabel *bsaLabel;
    QLabel *farVisionLabel;
    QLabel *nearVisionLabel;
};
