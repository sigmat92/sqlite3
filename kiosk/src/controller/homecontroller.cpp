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

    // ================= FINAL SIGNALS (SAVE TO DB) =================

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

    connect(m_vitalsModel, &VitalsModel::temperatureChanged,
        this, &HomeController::onTemperatureChanged);
        
    // ================= START REQUESTS =================

    connect(m_view, &HomeView::startTemperatureRequested,
            this, [this]() {

        if (!validatePatient())
            return;

        m_view->setTemperatureBusy(true);
        m_vitalsService->requestTemperature();
    });

    connect(m_view, &HomeView::startSpo2Requested,
            this, &HomeController::onStartSpo2Requested);

    // ================= LIVE UI UPDATES =================

    connect(m_vitalsModel, &VitalsModel::temperatureChanged,
            this, &HomeController::onTemperatureChanged);

    connect(m_vitalsModel, &VitalsModel::spo2Changed,
            this, &HomeController::onSpO2Changed);
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

    m_vitalsRepo->saveTemperature(sessionId, temp);
}
void HomeController::onSpO2Final(int spo2, int pulse)
{
    int sessionId = m_vitalsService->sessionId();
    if (sessionId <= 0) return;

    m_vitalsRepo->saveSpO2(sessionId, spo2, pulse);
}
void HomeController::onWeightFinal(double weight)
{
    int sessionId = m_vitalsService->sessionId();
    if (sessionId <= 0) return;

    m_vitalsRepo->saveWeight(sessionId, weight);
}
void HomeController::onHeightFinal(int height)
{
    int sessionId = m_vitalsService->sessionId();
    if (sessionId <= 0) return;

    m_vitalsRepo->saveHeight(sessionId, height);
}
void HomeController::onNIBPFinal(int sys, int dia)
{
    int sessionId = m_vitalsService->sessionId();
    if (sessionId <= 0) return;

    m_vitalsRepo->saveNIBP(sessionId, sys, dia);
}

void HomeController::onTemperatureChanged(double value, char unit)
{
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
void HomeController::onStartSpo2Requested()
{
    qDebug() << "SpO2 start requested";

    if (!validatePatient())
        return;

    m_vitalsService->requestSpo2();
}
void HomeController::visionTestRequested()
{
    qDebug() << "Vision test requested (stub)";
}