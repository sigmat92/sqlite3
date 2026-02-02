#include "homecontroller.h"
#include "view/homeview.h"
#include "service/sessionservice.h"
#include "storage/patientrepository.h"

HomeController::HomeController(HomeView* view,
                               SessionService* session,
                               PatientRepository* repo,
                               QObject* parent)
    : QObject(parent)
    , m_view(view)
    , m_session(session)
    , m_repo(repo)
{
    /* UI → Controller */
    //connect(m_view, &HomeView::startNewTest,
    //        this, &HomeController::onStartNewTest);

    /* Session → Controller */
    //connect(m_session, &SessionService::patientLoaded,
    //        this, &HomeController::onPatientLoaded);

    connect(m_session, &SessionService::vitalsUpdated,
            this, &HomeController::onVitalsUpdated);
}

/* -------- Slots -------- */
/*
void HomeController::onStartNewTest()
{
    // Reset current workflow
    m_session->reset();

    // Clear UI
    m_view->clearPatient();
    m_view->setSpO2(0, 0);
    m_view->setNIBP("---");

    // Optional: navigate to test screen later
}
*/
/*
void HomeController::onPatientLoaded()
{
    const auto& patient = m_session->currentPatient();

    m_view->setPatientName(patient.name);
    m_view->setMobile(patient.mobile);
    m_view->setAge(patient.age);
    m_view->setGender(patient.gender);
}
*/
void HomeController::onVitalsUpdated(int spo2, int pulse)
{
    m_view->setSpO2(spo2, pulse);

    // Persist snapshot (optional, debounced)
    m_repo->saveVitals(
        m_session->currentPatientId(),
        spo2,
        pulse
    );
}

