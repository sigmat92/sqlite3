
#include "homecontroller.h"
#include "view/homeview.h"
#include "service/sessionservice.h"
#include "storage/patientrepository.h"
#include "model/vitalsmodel.h"
#include "controller/protocolcontroller.h"
#include <QDebug>
HomeController::HomeController(HomeView* view,
                               SessionService* session,
                               PatientRepository* repo,
                               VitalsModel* vitals,
			       ProtocolController* protocol,
                               QObject* parent)
    : QObject(parent)
    , m_view(view)
    , m_session(session)
    , m_repo(repo)
    , m_vitals(vitals)
    , m_protocolController(protocol)
{
	    // when user presses start
	   connect(m_view, &HomeView::startTemperatureRequested, this, [this] {
    m_view->setTemperatureBusy(true);
    m_protocolController->requestTemperature();
});

/*
    connect(m_view, &HomeView::startTemperatureRequested, this, [] {
		        m_view->setTemperatureBusy(true);
    			m_protocolController->requestTemperature();
		    });
*/
            
    // Model → UI
    connect(m_vitals, &VitalsModel::temperatureChanged,
            this, &HomeController::onTemperatureChanged);
	
   connect(m_vitals, &VitalsModel::temperatureChanged,
        this, [](double v, char u){
            qDebug() << "HomeController SLOT HIT:" << v << u;
        });

/*
    connect(m_view, &HomeView::startTemperatureRequested,
        this, [] {
            qDebug() << "HomeController: forwarding temperature request";
        });

        connect(m_view, &HomeView::startTemperatureRequested,
        m_protocolController, &ProtocolController::requestTemperature);
	*/
}

void HomeController::onTemperatureChanged(double value, char unit)
{
    QString text = QString::number(value, 'f', 1)
                 + QChar(0x00B0)
                 + QChar(unit);

    qDebug() << "HomeController: updating UI =" << text;

    m_view->setTemperatureText(text);
    m_view->setTemperatureBusy(false);

    m_protocolController->setIdle();
}




/**
void HomeController::onTemperatureChanged(double value, char unit)
{
    QString text = QString::number(value, 'f', 1) +
                   QChar(0x00B0) + QChar(unit);

    qDebug() << "HomeController: updating UI =" << text;
    m_view->setTemperatureText(text);
}
*/

/*
void HomeController::onTemperatureChanged(double temp)
{
    qDebug() << "HomeController: updating UI =" << temp;
    m_view->setTemperature(temp);
}
*/
/*
HomeController::HomeController(HomeView* view,
                               SessionService* session,
                               PatientRepository* repo,
                               QObject* parent)
    : QObject(parent)
    , m_view(view)
    , m_session(session)
    , m_repo(repo)
{
    connect(m_view, &HomeView::startSpo2Requested,
            m_session, &SessionService::startSpo2);

    connect(m_view, &HomeView::startNibpRequested,
            m_session, &SessionService::startNibp);

    connect(m_view, &HomeView::startHeightRequested,
            m_session, &SessionService::startHeight);

    connect(m_view, &HomeView::startWeightRequested,
            m_session, &SessionService::startWeight);

    connect(m_view, &HomeView::startTemperatureRequested,
            m_session, &SessionService::startTemperature);
            
    connect(vitalsModel, &VitalsModel::temperatureChanged,
        this, &HomeController::onTemperatureChanged);
}

void HomeController::onTemperatureChanged(float temp)
{
    m_view->setTemperature(temp);
}
*/
/*
void HomeController::onVitalsUpdated(int spo2, int pulse)
{
    // Forward to view
    if (m_view) {
        m_view->setSpO2(spo2, pulse);
    }

    // Optional: persist
    if (m_repo && m_session) {
        m_repo->saveVitals(
            m_session->currentPatientId(),
            spo2,
            pulse
        );
    }
}
*/
