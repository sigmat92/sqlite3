#ifndef VITALSSERVICE_H
#define VITALSSERVICE_H

#include <QObject>
#include <QTimer>
#include "storage/vitalsrepository.h"
#include "model/vitalsmodel.h"

class VitalsService : public QObject
{
    Q_OBJECT

public:
    explicit VitalsService(QObject* parent=nullptr);

    void requestTemperature();
    void requestSpo2();
    void requestNibp();
    void requestWeight();
    void requestHeight();

    void setRepository(VitalsRepository* repo);
    void setSessionId(int id);
    int sessionId() const { return m_sessionId; }
    
    VitalsModel currentVitals() const; 

signals:
    void sendCommand(QByteArray);

    void temperatureReady(double,char);
    void spo2Ready(int,int);
    void nibpReady(int,int,int);
    void weightReady(double);
    void heightReady(int);

public slots:
    void onTemperature(double,char);
    void onSpo2(int,int);
    void onNibp(int,int,int);
    void onWeight(double);
    void onHeight(double);

private:
    enum class State { Idle, Temp, Spo2, Nibp, Weight, Height };
    State state = State::Idle;

    QTimer timeout;

    VitalsRepository* m_repo = nullptr;
    int m_sessionId = -1;
    
    void setIdle();
    void startTimeout();
  
    QString ntVitals;         //
    
};

#endif