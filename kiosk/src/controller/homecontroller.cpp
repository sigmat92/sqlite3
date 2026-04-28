#include "homecontroller.h"
#include "storage/patientrepository.h"
#include "../view/homeview.h"
#include "../service/sessionservice.h"
#include "../model/vitalsmodel.h"
#include "../storage/vitalsrepository.h"
#include "service/settingsservice.h"

#include <QDebug>
//global vitals
    double temperature=0.0;
    int spo2=0;
    int pulse=0;
    double weight=0.0;
    int height=0;
    int systolic=0;
    int diastolic=0;

HomeController::HomeController(HomeView* view,
               SessionService* sessionService,
               PatientRepository* repo,
               VitalsModel* vitalsModel,
               VitalsService* vitalsService,
               VitalsRepository* vitalsRepo,   // ADD THIS
               SettingsService* settings,
               QObject* parent)
: QObject(parent),
  m_view(view),
  m_sessionService(sessionService),
  m_repo(repo),
  m_vitalsModel(vitalsModel),
  m_settings(settings),        
  m_vitalsService(vitalsService)
{
    
    m_vitalsService = vitalsService;
    m_vitalsRepo = vitalsRepo;

    // ================= FINAL SIGNALS (SAVE TO DB) =================

    connect(m_vitalsModel, &VitalsModel::spo2Final,
            this, &HomeController::onSpO2Final);

    connect(m_vitalsModel, &VitalsModel::temperatureFinal,
            this, &HomeController::onTemperatureFinal,Qt::UniqueConnection);

    connect(m_vitalsModel, &VitalsModel::weightFinal,
            this, &HomeController::onWeightFinal);

    connect(m_vitalsModel, &VitalsModel::heightFinal,
            this, &HomeController::onHeightFinal);

    connect(m_vitalsModel, &VitalsModel::nibpFinal,
            this, &HomeController::onNIBPFinal);

    connect(m_vitalsModel, &VitalsModel::temperatureChanged,
        this, &HomeController::onTemperatureChanged,Qt::UniqueConnection);

    connect(m_view, &HomeView::resetSessionRequested,
        this, &HomeController::resetSession);
        
    // ================= START REQUESTS =================

    //1.vision test

    connect(m_view, &HomeView::visionTestRequested,
        this, [this]() {
            qDebug() << "homecontroller: \"Vision Test\" requested "<< "with sessionId:" << m_vitalsService->sessionId();

            //if (!ensurePatientSaved())
            //    return;
            //m_view->setCurrentSessionId(m_currentSessionId);
            emit visionTestRequested();
            //emit visionTestRequested(sessionId);
            
    });

    //2.temperature

    connect(m_view, &HomeView::startTemperatureRequested,
        this, [this] {

    qDebug() << "homecontroller: \"Temperature\" requested "<< "with sessionId:" << m_vitalsService->sessionId();

            //if (!ensurePatientSaved())
            //    return;

            m_view->setTemperatureBusy(true);

            m_vitalsService->requestTemperature();
    });

    //3.spo2/pulse

    connect(m_view, &HomeView::startSpo2Requested,
        this, [this] {

    qDebug() << "homecontroller: \"startSpo2Requested\" requested "<< "with sessionId:" << m_vitalsService->sessionId();

            //if (!ensurePatientSaved())
            //    return;

            m_view->setSpO2Busy(true);

            m_vitalsService->requestSpo2();
    });

    //4.NIBP
    connect(m_view, &HomeView::startNIBPRequested,
        this, [this] {

    qDebug() << "homecontroller: \"startNIBPRequested\" requested "<< "with sessionId:" << m_vitalsService->sessionId();

            //if (!ensurePatientSaved())
            //    return;

            m_view->setNIBPBusy(true);

            m_vitalsService->requestNibp();
    });

    //5.height
    connect(m_view, &HomeView::startHeightRequested,
        this, [this] {

    qDebug() << "homecontroller: \"startHeightRequested\" requested "<< "with sessionId:" << m_vitalsService->sessionId();

            //if (!ensurePatientSaved())
            //    return;

            m_view->setHeightBusy(true);

            m_vitalsService->requestHeight();
    });
        
    //6.weight
    connect(m_view, &HomeView::startWeightRequested,
        this, [this] {

    qDebug() << "homecontroller: \"startWeightRequested\" requested "<< "with sessionId:" << m_vitalsService->sessionId();

            //if (!ensurePatientSaved())
            //    return;

            m_view->setWeightBusy(true);

            m_vitalsService->requestWeight();
    });

    // ================= LIVE UI UPDATES =================

    connect(m_vitalsModel, &VitalsModel::temperatureChanged,
            this, &HomeController::onTemperatureChanged,Qt::UniqueConnection);

    connect(m_vitalsModel, &VitalsModel::spo2Changed,
            this, &HomeController::onSpO2Changed,Qt::UniqueConnection);

    connect(m_vitalsModel, &VitalsModel::nibpChanged,
            this, &HomeController::onNIBPChanged,Qt::UniqueConnection);

    connect(m_vitalsModel, &VitalsModel::heightChanged,
            this, &HomeController::onHeightChanged,Qt::UniqueConnection);

    connect(m_vitalsModel, &VitalsModel::weightChanged,
            this, &HomeController::onWeightChanged,Qt::UniqueConnection);

}
bool HomeController::validatePatient()
{
    QString name = m_view->patientName();
    QString ageStr = m_view->patientAge();
    QString gender = m_view->patientGender();

    if (name.isEmpty() || ageStr.isEmpty() || gender.isEmpty())
    {
        m_view->showError("Please fill patient details");
        return false;
    }

    if (ageStr.toInt() <= 0)
    {
        m_view->showError("Invalid age");
        return false;
    }

    return true;
}
void HomeController::onTemperatureFinal(double temp)
{
    int sessionId = m_vitalsService->sessionId();

    if (sessionId <= 0)
    {
        qDebug() << "Invalid session. Skipping temperature save.";
        return;
    }

    //m_vitalsRepo->saveTemperature(sessionId, temp);
    //temperature=temp;
    qDebug() << "temperature not saved in controller with sessionId:" << m_vitalsService->sessionId();
}

void HomeController::onSpO2Final(int spo2, int pulse)
{
    int sessionId = m_vitalsService->sessionId();
    if (sessionId <= 0) return;

    //m_vitalsRepo->saveSpO2(sessionId, spo2, pulse);
    //spo2=spo2;
    //pulse=pulse;
}
void HomeController::onWeightFinal(double weight)
{
    int sessionId = m_vitalsService->sessionId();
    if (sessionId <= 0) return;

    //m_vitalsRepo->saveWeight(sessionId, weight);
    //weight=weight;

}
void HomeController::onHeightFinal(int height)
{
    int sessionId = m_vitalsService->sessionId();
    if (sessionId <= 0) return;

    //m_vitalsRepo->saveHeight(sessionId, height);
    //height=height;

}
void HomeController::onNIBPFinal(int sys, int dia)
{
    int sessionId = m_vitalsService->sessionId();
    if (sessionId <= 0) return;

    //m_vitalsRepo->saveNIBP(sessionId, sys, dia);
    //sys=sys;
    //dia=dia;

}

void HomeController::onWeightChanged(double weight)
{
    QString text = QString::number(weight, 'f', 1) + " kg";
    m_view->setWeightText(text);
    m_view->setWeightBusy(false);
    weight=weight;
}
void HomeController::onHeightChanged(int height)
{
    QString text = QString::number(height) + " cm";
    m_view->setHeightText(text);
    m_view->setHeightBusy(false);
    height=height;
}
void HomeController::onNIBPChanged(int sys, int dia)
{
    QString text = QString("%1 / %2").arg(sys).arg(dia);
    m_view->setNIBPText(text);
    m_view->setNIBPBusy(false);
    systolic=sys;
    diastolic=dia;
}

void HomeController::onTemperatureChanged(double value, char unit)
{
    QString text = QString::number(value, 'f', 1)
                 + QChar(0x00B0)
                 + QChar(unit);

    m_view->setTemperatureText(text);
    m_view->setTemperatureBusy(false);
    temperature=value;
}

void HomeController::onSpO2Changed(int spo2, int pulse)
{
    QString text = QString("%1 / %2").arg(spo2).arg(pulse);
    m_view->setSpo2Text(text);
    m_view->setSpO2Busy(false);
    spo2=spo2;
    pulse=pulse;
}
void HomeController::onStartSpo2Requested()
{
    qDebug() << "SpO2 start requested";

    //if (!validatePatient())
    //    return;

    m_vitalsService->requestSpo2();
}

bool HomeController::ensurePatientSaved()
{
    qDebug() << "Ensuring patient/session...";

    if (m_currentSessionId > 0)
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

    qDebug() << "Creating session in controller...";

    m_currentSessionId = m_sessionService->createSession(patientId);

    if (m_currentSessionId <= 0)
    {
        m_view->showError("Failed to create session");
        return false;
    }

    // CRITICAL 
    m_vitalsService->setSessionId(m_currentSessionId);

    qDebug() << "Session setting in vitals service from home controller:" << m_currentSessionId;

    //save vitals 0 for now
    int sessionId=m_currentSessionId;
    qDebug() << "in home controller sessionId:" << sessionId;
    //m_vitalsRepo->saveSession(sessionId);
    //qDebug() << "Saving initial vitals with sessionId:" << sessionId;
    m_vitalsRepo->saveTemperature(sessionId, temperature);
    qDebug() << "temperature : " << temperature << " saved in DB from controller with sessionId:" << sessionId;
    m_vitalsRepo->saveSpO2(sessionId, spo2, pulse);
    qDebug() << "spo2 : " << spo2 << " saved in DB from controller with sessionId:" << sessionId;
    m_vitalsRepo->saveWeight(sessionId, weight);
    qDebug() << "weight : " << weight << " saved in DB from controller with sessionId:" << sessionId;
    m_vitalsRepo->saveHeight(sessionId, height);
    qDebug() << "height : " << height << " saved in DB from controller with sessionId:" << sessionId;
    m_vitalsRepo->saveNIBP(sessionId, systolic, diastolic);
    qDebug() << "NIBP : " << systolic << "/" << diastolic << " saved in DB from controller with sessionId:" << sessionId;


    m_view->setCurrentSessionId(m_currentSessionId);
    m_view->lockPatientFields();

    return true;
}
void HomeController::resetSession()
{
    qDebug() << "Resetting session in controller";

    m_currentPatientId = -1;
    m_currentSessionId = -1;

    // CRITICAL
    m_vitalsService->setSessionId(-1);

    m_view->unlockPatientFields();
    m_view->clearPatientFields();
}
void HomeController::visionTestRequested()
{
    qDebug() << "Vision test requested (stub) with sessionId:" << m_vitalsService->sessionId();
}