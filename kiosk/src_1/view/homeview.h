#pragma once

#include <QWidget>

class QLabel;
class QLineEdit;
class QRadioButton;
class MetricCard;

class HomeView : public QWidget
{
    Q_OBJECT

public:
    explicit HomeView(QWidget* parent = nullptr);

    // Patient API
    void clearPatient();
    void setPatientName(const QString&);
    void setMobile(const QString&);
    void setAge(int);
    void setGender(const QString&);

    // Metrics API
    void setSpO2(int spo2, int pulse);
    void setNIBP(const QString&);
    void setHeight(int);
    void setWeight(double);
    void setTemperature(double);
    
    void setTemperatureText(const QString& text);
    void setTemperatureBusy(bool busy);  

signals:

    void startTemperatureRequested();
    void startSpo2Requested();
    void startNIBPRequested();
    void startHeightRequested();
    void startWeightRequested();
    void startVisionTestRequested();
    void startNewTestRequested();
    void startSettingsRequested();
    void startPrintingRequested();
    void visionTestRequested();

public slots:
    void onVitalsUpdated(int spo2, int pulse);
    


private:
    /* ---------- Header ---------- */
    QLabel* m_timeLabel{nullptr};

    /* ---------- Patient fields ---------- */
    QLineEdit* nameEdit{nullptr};
    QLineEdit* mobileEdit{nullptr};
    QLineEdit* ageEdit{nullptr};
    QRadioButton* maleBtn{nullptr};
    QRadioButton* femaleBtn{nullptr};

    /* ---------- Metric values ---------- */

    MetricCard* temperatureCard{nullptr};
    MetricCard* spo2Card{nullptr};
    MetricCard* nibpCard{nullptr};
    MetricCard* heightCard{nullptr};
    MetricCard* weightCard{nullptr};
    MetricCard* visionTestCard{nullptr};
};

