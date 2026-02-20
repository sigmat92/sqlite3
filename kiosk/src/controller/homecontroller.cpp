
#include "homecontroller.h"
#include "view/homeview.h"
#include "service/sessionservice.h"
#include "storage/patientrepository.h"
#include "model/vitalsmodel.h"
#include "controller/protocolcontroller.h"
#include "service/settingsservice.h"
#include "storage/patientrepository.h"
#include "model/vitalsmodel.h"
#include "controller/protocolcontroller.h"
#include "view/visiontestview.h"
#include "controller/visiontestcontroller.h"
#include "view/settingsview.h"

#include <QDebug>

HomeController::HomeController(HomeView* v,
                               SessionService* s,
                               PatientRepository* r,
                               VitalsModel* vm,
                               ProtocolController* pc,
                               SettingsService* ss,
                               QObject* parent)
    : QObject(parent),
      m_view(v),
      m_session(s),
      m_repo(r),
      m_vitals(vm),
      m_protocol(pc),
      m_settingsService(ss)

/*
HomeController::HomeController(HomeView* view,
                               SessionService* session,
                               PatientRepository* repo,
                               VitalsModel* vitals,
			                   ProtocolController* protocol,
                               SettingsService* settingsService,
                               QObject* parent)
    : QObject(parent)
    , m_view(view)
    , m_session(session)
    , m_repo(repo)
    , m_vitals(vitals)
    , m_protocolController(protocol)
    , m_settingsService(settingsService)
*/
{
	// when user presses startTemperatureRequested
    
	connect(m_view, &HomeView::startTemperatureRequested, this, [this] {
    m_view->setTemperatureBusy(true);
    
    m_protocol->requestTemperature();
    //added
});

connect(m_view, &HomeView::settingsRequested,
        this, [this]() {

    qDebug() << "HomeController: opening SettingsView";

    SettingsView* settingsView = new SettingsView;
    settingsView->setModel(m_settingsService->getModel());
    settingsView->show();
    //settingsView->showFullScreen();
});
            
    // Model → UI
    connect(m_vitals, &VitalsModel::temperatureChanged,
            this, &HomeController::onTemperatureChanged);
	
   connect(m_vitals, &VitalsModel::temperatureChanged,
        this, [](double v, char u){
            qDebug() << "HomeController SLOT HIT:" << v << u;
        });

    connect(m_vitals, &VitalsModel::spo2Changed,
            this, &HomeController::onSpO2Changed);
        

    connect(m_vitals, &VitalsModel::spo2Changed,
        this, [](int spo2, int pulse){
            qDebug() << "HomeController SLOT HIT:" << spo2 << pulse;
        });
    
    //connect(view, &HomeView::visionTestRequested, this, [this]() {
    //auto* v = new VisionTestView;
    //new VisionTestController(v, v);
    //v->showFullScreen();   // kiosk mode
//});

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

    //m_protocolController->setIdle();
    
    m_protocol->setIdle();
}

void HomeController::onSpO2Changed(int spo2, int pulse)
{
    //m_view->setSpO2(spo2, pulse);
}

 //SettingsModel* HomeController::getModel() const
//{
//    return m_settingsService->getModel();
    //settingsView->setModel(m_settingsService->getModel());

//}