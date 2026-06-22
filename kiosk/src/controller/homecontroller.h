#pragma once

#include <QObject>
#include "service/vitalsservice.h" 

class HomeView;
class SessionService;
class PatientRepository;
class VitalsModel;
class ProtocolController;
class SettingsService;
class VitalsRepository;
class VisionTestView;

class HomeController : public QObject
{
    Q_OBJECT

public:
        HomeController(HomeView* view,
               SessionService* sessionService,
               PatientRepository* repo,
               VitalsModel* vitalsModel,
               VitalsService* vitalsService,
               VitalsRepository* vitalsRepo,   // ADD THIS
               SettingsService* settings,
               QObject* parent);

        bool ensurePatientSaved();
        
public slots:
    void onTemperatureChanged(double value, char unit);
    void onSpO2Changed(int spo2, int pulse);
    void onNIBPChanged(int sys, int dia);
    void onHeightChanged(int height);
    void onWeightChanged(double weight);
    void onStartSpo2Requested();
    void visionTestRequested();
    //void onNIBPPressureChanged(int pressure);

private slots:
    void onSpO2Final(int spo2, int pulse);
    void onTemperatureFinal(double temp);
    void onWeightFinal(double weight);
    void onHeightFinal(int height);
    void onNIBPFinal(int sys, int dia);
    
    void onNIBPPressureChanged(int pressure);
    
    void onVisionChanged(
        const QString& near,
        const QString& far);

    void onVisionFinal(
        const QString& near,
        const QString& far);
    //void onNibpPressure(int pressure);
private:
    VisionTestView* m_visionView = nullptr;
    bool validatePatient();
    
    void resetSession();

    HomeView* m_view;
    SessionService* m_sessionService;
    PatientRepository* m_repo;
    VitalsModel* m_vitalsModel;
    ProtocolController* m_protocol;
    SettingsService* m_settings;

    VitalsRepository* m_vitalsRepo;

    int m_currentPatientId = -1;
    int m_currentSessionId = -1;
    VitalsService* m_vitalsService;

    //health metrics live updates

    double m_weightKg = 0.0;
    int    m_heightCm = 0;

    double m_bmi = 0.0;
    double m_bmr = 0.0;
    double m_bsa = 0.0;

    void updateDerivedMetrics();
};
