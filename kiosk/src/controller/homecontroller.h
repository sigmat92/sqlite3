#pragma once

#include <QObject>

class HomeView;
class SessionService;
class PatientRepository;

class HomeController : public QObject
{
    Q_OBJECT
public:
    explicit HomeController(HomeView* view,
                            SessionService* session,
                            PatientRepository* repo,
                            QObject* parent = nullptr);

public slots:
    //void onStartNewTest();
    void onVitalsUpdated(int spo2, int pulse);
    //void onPatientLoaded();

private:
    HomeView* m_view;
    SessionService* m_session;
    PatientRepository* m_repo;
};

