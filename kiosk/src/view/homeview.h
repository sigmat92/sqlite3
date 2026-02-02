#pragma once

#include <QWidget>
#include <QLabel>
/*
class HomeView : public QWidget
{
    Q_OBJECT
public:
    explicit HomeView(QWidget* parent = nullptr);
    void clearPatient();
    void setPatientName(const QString& name);
    void setMobile(const QString& mobile);
    void setAge(int age);
    void setGender(const QString& gender);

signals:
    void startNewTest();      // user intent
    void printRequested();
    void visionTestRequested();

public slots:
    void setSpO2(int spo2, int pulse);
    void setNIBP(const QString& value);
    void setHeight(int cm);
    void setWeight(double kg);
    void setTemperature(double f);

private:
    QLabel* m_timeLabel;
    QLabel* spo2Value{nullptr};
    QLabel* nibpValue{nullptr};
    QLabel* heightValue{nullptr};
    QLabel* weightValue{nullptr};
    QLabel* tempValue{nullptr};
    //QLabel* wifiIcon;
};
*/
class QLineEdit;
class QRadioButton;
class QPushButton;
class QTimer;
class HomeView : public QWidget
{
    Q_OBJECT
public:
    explicit HomeView(QWidget* parent = nullptr);

    void clearPatient();
    void setPatientName(const QString&);
    void setMobile(const QString&);
    void setAge(int);
    void setGender(const QString&);

    void setSpO2(int spo2, int pulse);
    void setNIBP(const QString&);
    void setHeight(int);
    void setWeight(double);
    void setTemperature(double);

private:
    // Patient fields
    QLineEdit* nameEdit{nullptr};
    QLineEdit* mobileEdit{nullptr};
    QLineEdit* ageEdit{nullptr};
    QRadioButton* maleBtn{nullptr};
    QRadioButton* femaleBtn{nullptr};

    // Metric values
    QLabel* spo2Value{nullptr};
    QLabel* nibpValue{nullptr};
    QLabel* heightValue{nullptr};
    QLabel* weightValue{nullptr};
    QLabel* tempValue{nullptr};

    QLabel* m_timeLabel{nullptr};
};
