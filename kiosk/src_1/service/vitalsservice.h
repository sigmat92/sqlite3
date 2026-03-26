#pragma once
#include <QObject>
#include <QTimer>

enum class State {
    Idle,
    Temp,
    Spo2,
    Nibp,
    Weight,
    Height
};

class VitalsService : public QObject {
    Q_OBJECT
public:
    explicit VitalsService(QObject* parent=nullptr);

    void requestTemperature();
    void requestSpo2();
    void requestNibp();
    void requestWeight();
    void requestHeight();

signals:
    void sendCommand(QByteArray);
    void temperatureReady(double, char);
    void spo2Ready(int,int);
    void nibpReady(int,int,int);
    void weightReady(double);
    void heightReady(double);

public slots:
    void onTemperature(double,char);
    void onSpo2(int,int);
    void onNibp(int,int,int);
    void onWeight(double);
    void onHeight(double);

private:
    State state{State::Idle};
    QTimer timeout;

    void setIdle();
    void startTimeout();
};