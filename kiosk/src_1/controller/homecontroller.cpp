#include "homecontroller.h"
#include "storage/patientrepository.h"
#include "../view/homeview.h"
#include "../service/sessionservice.h"
#include "../model/vitalsmodel.h"
#include "../storage/vitalsrepository.h"
#include "service/settingsservice.h"

#include <QDebug>

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

            if (!ensurePatientSaved())
                return;
            m_view->setCurrentSessionId(m_currentSessionId);
            emit visionTestRequested();
            //emit visionTestRequested(sessionId);
            
    });

    //2.temperature

    connect(m_view, &HomeView::startTemperatureRequested,
        this, [this] {

    qDebug() << "homecontroller: \"Temperature\" requested "<< "with sessionId:" << m_vitalsService->sessionId();

            if (!ensurePatientSaved())
                return;

            m_view->setTemperatureBusy(true);

            m_vitalsService->requestTemperature();
    });

    //3.spo2/pulse

    connect(m_view, &HomeView::startSpo2Requested,
        this, [this] {

    qDebug() << "homecontroller: \"startSpo2Requested\" requested "<< "with sessionId:" << m_vitalsService->sessionId();

            if (!ensurePatientSaved())
                return;

            m_view->setSpO2Busy(true);

            m_vitalsService->requestSpo2();
    });

    //4.NIBP
    connect(m_view, &HomeView::startNIBPRequested,
        this, [this] {

    qDebug() << "homecontroller: \"startNIBPRequested\" requested "<< "with sessionId:" << m_vitalsService->sessionId();

            if (!ensurePatientSaved())
                return;

            m_view->setNIBPBusy(true);

            m_vitalsService->requestNibp();
    });

    //5.height
    connect(m_view, &HomeView::startHeightRequested,
        this, [this] {

    qDebug() << "homecontroller: \"startHeightRequested\" requested "<< "with sessionId:" << m_vitalsService->sessionId();

            if (!ensurePatientSaved())
                return;

            m_view->setHeightBusy(true);

            m_vitalsService->requestHeight();
    });
        
    //6.weight
    connect(m_view, &HomeView::startWeightRequested,
        this, [this] {

    qDebug() << "homecontroller: \"startWeightRequested\" requested "<< "with sessionId:" << m_vitalsService->sessionId();

            if (!ensurePatientSaved())
                return;

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

    connect(m_vitalsModel, &VitalsModel::nibpPressureChanged,
            this, &HomeController::onNIBPPressureChanged,Qt::UniqueConnection);


        //bool ok = connect(m_vitalsService,
        //          &VitalsService::nibpPressure,
        //          this,
        //          &HomeController::onNibpPressure);

//qDebug() << "NIBP pressure connect:" << ok;

    //connect(m_vitalsService,
    //        &VitalsService::nibpPressure,
    //        this,
    //        &HomeController::onNibpPressure,
    //        Qt::UniqueConnection);
    
    
    // ================= OTHER UI ACTIONS =================
    connect(m_vitalsService,
        &VitalsService::measurementFinished,
        this,
        [this](VitalsService::State s)
{
    switch(s)
    {
        case VitalsService::State::Spo2:
            m_view->setSpO2Busy(false);
            break;

        case VitalsService::State::Temp:
            m_view->setTemperatureBusy(false);
            break;

        case VitalsService::State::Nibp:
            m_view->setNIBPBusy(false);
            break;

        case VitalsService::State::Weight:
            m_view->setWeightBusy(false);
            break;

        case VitalsService::State::Height:
            m_view->setHeightBusy(false);
            break;

        default:
            break;
    }
});

//
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
    //int sessionId = m_vitalsService->sessionId();

    //if (sessionId <= 0)
    //{
    //    qDebug() << "Invalid session. Skipping temperature save.";
    //    return;
    //}

    //m_vitalsRepo->saveTemperature(sessionId, temp);
    
    //qDebug() << "temperature:" << temp << "saved in controller with sessionId:" << m_vitalsService->sessionId();
}

void HomeController::onSpO2Final(int spo2, int pulse)
{
    //int sessionId = m_vitalsService->sessionId();
    //if (sessionId <= 0)
    //{
    //    qDebug() << "Invalid session. Skipping SpO2/pulse save.";
    //    return;
    //}

    //m_vitalsRepo->saveSpO2(sessionId, spo2, pulse);
    //qDebug() << "spo2:" << spo2 << "pulse:" << pulse << "saved in controller with sessionId:" << m_vitalsService->sessionId();
}
void HomeController::onWeightFinal(double weight)
{
    //int sessionId = m_vitalsService->sessionId();
    //if (sessionId <= 0)
    //{
    //    qDebug() << "Invalid session. Skipping weight save.";
    //    return;
    //}

    //m_vitalsRepo->saveWeight(sessionId, weight);
    //qDebug() << "weight:" << weight << "saved in controller with sessionId:" << m_vitalsService->sessionId();
}
void HomeController::onHeightFinal(int height)
{
    //int sessionId = m_vitalsService->sessionId();
    //if (sessionId <= 0)
    //{
    //    qDebug() << "Invalid session. Skipping height save.";
    //    return;
   // }

    //m_vitalsRepo->saveHeight(sessionId, height);
    //qDebug() << "height:" << height << "saved in controller with sessionId:" << m_vitalsService->sessionId();
}
void HomeController::onNIBPFinal(int sys, int dia)
{
    //int sessionId = m_vitalsService->sessionId();
    //if (sessionId <= 0)
    //{
    //    qDebug() << "Invalid session. Skipping NIBP save.";
    //    return;
    //}

    //m_vitalsRepo->saveNIBP(sessionId, sys, dia);

    //qDebug() << "nibp:" << sys << "/" << dia << "saved in controller with sessionId:" << m_vitalsService->sessionId();

}

void HomeController::onWeightChanged(double weight)
{
    QString text = QString::number(weight, 'f', 1) + " kg";
    m_view->setWeightText(text);
    //m_view->setWeightBusy(false);
    
}
void HomeController::onHeightChanged(int height)
{
    QString text = QString::number(height) + " cm";
    m_view->setHeightText(text);
    //m_view->setHeightBusy(false);
    
}
void HomeController::onNIBPChanged(int sys, int dia)
{
    QString text =
        QString("%1 / %2").arg(sys).arg(dia);

    m_view->setNIBPText(text);

    m_view->setNIBPBusy(false);
}
//void HomeController::onNIBPChanged(int sys, int dia)
//{
//    QString text = QString("%1 / %2").arg(sys).arg(dia);
//    m_view->setNIBPText(text);
    //m_view->setNIBPBusy(false);

//}

//void HomeController::onNibpPressure(int pressure)
//{
//    qDebug() << "[UI] Pressure update:" << pressure;

//    QString text =
//        QString("Pressure: %1 mmHg").arg(pressure);

//    m_view->setNIBPText(text);
//}
void HomeController::onNIBPPressureChanged(int pressure)
{
    QString text =
        QString(" %1 ").arg(pressure);

    m_view->setNIBPText(text);

    // REMOVE THIS
    // m_view->setNIBPBusy(true);
}
/*
void HomeController::onNIBPPressureChanged(int pressure)
{
    qDebug() << "[home controller] Live Pressure:" << pressure;

    QString text =
        QString("%1").arg(pressure);

    m_view->setNIBPText(text);

    // measurement still running
    m_view->setNIBPBusy(true);
}
*/
void HomeController::onTemperatureChanged(double value, char unit)
{
    QString text = QString::number(value, 'f', 1)
                 + QChar(0x00B0)
                 + QChar(unit);

    m_view->setTemperatureText(text);
    //m_view->setTemperatureBusy(false);
}

void HomeController::onSpO2Changed(int spo2, int pulse)
{
    QString text = QString("%1 / %2").arg(spo2).arg(pulse);
    m_view->setSpo2Text(text);
    //m_view->setSpO2Busy(false);

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