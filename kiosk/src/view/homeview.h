#pragma once

#include <QWidget>

class QLabel;
class QLineEdit;
class QRadioButton;

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

signals:
    void startSpo2Requested();
    void startNibpRequested();
    void startHeightRequested();
    void startWeightRequested();
    void startTemperatureRequested();
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
    QLabel* spo2Value{nullptr};
    QLabel* nibpValue{nullptr};
    QLabel* heightValue{nullptr};
    QLabel* weightValue{nullptr};
    QLabel* tempValue{nullptr};
};
