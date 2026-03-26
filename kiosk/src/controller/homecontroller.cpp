#include "homecontroller.h"
#include "storage/patientrepository.h"
#include "../view/homeview.h"
#include "../service/sessionservice.h"
#include "../model/vitalsmodel.h"
#include "../storage/vitalsrepository.h"
#include "storage/vitalsrepository.h"
//#include "controller/protocolcontroller.h"
#include "service/settingsservice.h"
#include "../view/settingsview.h"
#include "../controller/settingscontroller.h"
#include "../service/systemsettingsservice.h"
#include "../service/adminauthservice.h"
#include "view/visiontestview.h"
#include <QDebug>

HomeController::HomeController(HomeView* view,
                               SessionService* sessionService,
                               PatientRepository* repo,
                               VitalsModel* vitalsModel,
                               VitalsService* vitalsService,   
                               SettingsService* settings,
                               QObject* parent)
: QObject(parent),
  m_view(view),
  m_sessionService(sessionService),
  m_repo(repo),
  m_vitalsModel(vitalsModel),
  m_vitalsService(vitalsService),   
  m_settings(settings)
{
    m_vitalsRepo = new VitalsRepository();
    m_vitalsService = vitalsService;

    //settings
        connect(m_view, &HomeView::settingsRequested,
            this, [this]()
    {
        SettingsView* settingsView = new SettingsView;
        SystemSettingsService* systemService = new SystemSettingsService;
        AdminAuthService* authService = new AdminAuthService;

        new SettingsController(settingsView,
                            systemService,
                            authService);

        //settingsView->show();
        settingsView->showFullScreen();
    });

    //visionTest
//
        connect(m_view, &HomeView::visionTestRequested,
            this, [this]()
    {
        VisionTestView* visionTestView = new VisionTestView;
        SystemSettingsService* systemService = new SystemSettingsService;
        AdminAuthService* authService = new AdminAuthService;

        //new SettingsController(visionTestView,
        //                    systemService,
        //                    authService);

        //settingsView->show();
        visionTestView->showFullScreen();
    });

    
//

    // ===== FINAL SIGNALS (Save to DB) =====

    connect(m_vitalsModel, &VitalsModel::spo2Final,
            this, &HomeController::onSpO2Final);

    connect(m_vitalsModel, &VitalsModel::temperatureFinal,
            this, &HomeController::onTemperatureFinal);

    connect(m_vitalsModel, &VitalsModel::weightFinal,
            this, &HomeController::onWeightFinal);

    connect(m_vitalsModel, &VitalsModel::heightFinal,
            this, &HomeController::onHeightFinal);

    connect(m_vitalsModel, &VitalsModel::nibpFinal,
            this, &HomeController::onNIBPFinal);

    // ===== START REQUESTS =====

    connect(m_view, &HomeView::startSpo2Requested,
            this, &HomeController::onStartSpo2Requested);

    connect(m_view, &HomeView::startTemperatureRequested,
            this, [this] {
                if (!ensurePatientSaved())
                    return;

                m_view->setTemperatureBusy(true);
                //m_protocol->requestTemperature();
                m_vitalsService->requestTemperature();
            });

    // ===== LIVE STREAMING TO UI =====

    connect(m_vitalsModel, &VitalsModel::temperatureChanged,
            this, &HomeController::onTemperatureChanged);

    connect(m_vitalsModel, &VitalsModel::spo2Changed,
            this, &HomeController::onSpO2Changed);
}

bool HomeController::ensurePatientSaved()
{
    qDebug() << "Ensuring patient is saved...";
    if (m_currentPatientId > 0)
        return true;

    QString name = m_view->patientName();
    QString ageStr = m_view->patientAge();
    QString mobile = m_view->patientMobile();
    QString gender = m_view->patientGender();

    if (name.isEmpty() || ageStr.isEmpty() || gender.isEmpty())
    {
        m_view->showError("Please fill patient details");
        return false;
    }

    int age = ageStr.toInt();
    if (age <= 0)
    {
        m_view->showError("Invalid age");
        return false;
    }

    int patientId = m_repo->savePatient(name, age, mobile, gender);

    if (patientId <= 0)
    {
        m_view->showError("Failed to save patient");
        return false;
    }

    m_currentPatientId = patientId;

    // CREATE SESSION
    m_currentSessionId = m_sessionService->createSession(patientId);

    if (m_currentSessionId <= 0)
    {
        m_view->showError("Failed to create session");
        return false;
    }

    m_view->lockPatientFields();

    return true;
}

void HomeController::onSpO2Final(int spo2, int pulse)
{
    if (!ensurePatientSaved())
        return;

    m_vitalsRepo->saveSpO2(m_currentSessionId, spo2, pulse);
}

void HomeController::onTemperatureFinal(double temp)
{
    if (!ensurePatientSaved())
        return;

    m_vitalsRepo->saveTemperature(m_currentSessionId, temp);
}

void HomeController::onWeightFinal(double weight)
{
    if (!ensurePatientSaved())
        return;

    m_vitalsRepo->saveWeight(m_currentSessionId, weight);
}

void HomeController::onHeightFinal(int height)
{
    if (!ensurePatientSaved())
        return;

    m_vitalsRepo->saveHeight(m_currentSessionId, height);
}

void HomeController::onNIBPFinal(int sys, int dia)
{
    if (!ensurePatientSaved())
        return;

    m_vitalsRepo->saveNIBP(m_currentSessionId, sys, dia);
}
void HomeController::onTemperatureChanged(double value, char unit)
{
    qDebug() << "UI TEMP UPDATE:" << value << unit;

    QString text = QString::number(value, 'f', 1)
                 + QChar(0x00B0)
                 + QChar(unit);

    m_view->setTemperatureText(text);
    m_view->setTemperatureBusy(false);
}
void HomeController::onSpO2Changed(int spo2, int pulse)
{
    Q_UNUSED(spo2)
    Q_UNUSED(pulse)
}

void HomeController::resetSession()
{
    m_currentPatientId = -1;
    m_currentSessionId = -1;

    m_view->unlockPatientFields();
    m_view->clearPatientFields();
}

void HomeController::onStartSpo2Requested()
{
    qDebug() << "SpO2 start requested";

    if (!ensurePatientSaved())
        return;

    //m_protocol->requestSpo2();
}

void HomeController::visionTestRequested()
{
    qDebug() << "HomeController: launching Vision Test";

    if (!m_visionView)
    {
        m_visionView = new VisionTestView();

        connect(m_visionView,
                &VisionTestView::exitRequested,
                this,
                [this]()
                {
                    m_visionView->hide();
                    m_view->showFullScreen();
                });
    }

    m_view->hide();
    m_visionView->showFullScreen();
}
