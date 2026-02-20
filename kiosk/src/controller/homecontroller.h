#pragma once

#include <QObject>

class HomeView;
class SessionService;
class PatientRepository;
class VitalsModel;
class ProtocolController; 
class SettingsService;

class HomeController : public QObject
{
    Q_OBJECT
public:

    explicit HomeController(HomeView* v,
                        SessionService* s,
                        PatientRepository* r,
                        VitalsModel* vm,
                        ProtocolController* pc,
                        SettingsService* ss,
                        QObject* parent=nullptr);


    //explicit HomeController(HomeView* view,
    //                        SessionService* session,
    //                        PatientRepository* repo,
    //                        VitalsModel* vitalsModel,
    //                        ProtocolController* protocol,
    //                        QObject* parent = nullptr);
//public slots:
//    void onTemperatureChanged(double temp);
public slots:
    void onTemperatureChanged(double value, char unit);
    void onSpO2Changed(int spo2, int pulse);
    //void onSpO2Changed(int spo2, int pulse);
    //void onStartNewTest();
    //void onVitalsUpdated(int spo2, int pulse);
    //void onPatientLoaded();

private:
    HomeView* m_view;
    SessionService* m_session;
    PatientRepository* m_repo;
    VitalsModel* m_vitals;
    ProtocolController* m_protocol;
    SettingsService* m_settingsService;

};


