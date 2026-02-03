#pragma once

#include <QObject>

class HomeView;
class SessionService;
class PatientRepository;
class VitalsModel;

class HomeController : public QObject
{
    Q_OBJECT
public:
    explicit HomeController(HomeView* view,
                            SessionService* session,
                            PatientRepository* repo,
                            VitalsModel* vitalsModel,
                            QObject* parent = nullptr);
public slots:
    void onTemperatureChanged(float temp);

    //void onStartNewTest();
    //void onVitalsUpdated(int spo2, int pulse);
    //void onPatientLoaded();

private:
    HomeView* m_view;
    SessionService* m_session;
    PatientRepository* m_repo;
    VitalsModel* m_vitals;
};


