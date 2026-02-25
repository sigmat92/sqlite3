#pragma once

#include <QObject>

class HomeView;
class SessionService;
class PatientRepository;
class VitalsModel;
class ProtocolController;
class SettingsService;
class VitalsRepository;

class HomeController : public QObject
{
    Q_OBJECT

public:
    explicit HomeController(HomeView* view,
                            SessionService* sessionService,
                            PatientRepository* repo,
                            VitalsModel* vitalsModel,
                            ProtocolController* protocol,
                            SettingsService* settings,
                            QObject* parent = nullptr);

public slots:
    void onTemperatureChanged(double value, char unit);
    void onSpO2Changed(int spo2, int pulse);
    void onStartSpo2Requested();

private slots:
    void onSpO2Final(int spo2, int pulse);
    void onTemperatureFinal(double temp);
    void onWeightFinal(double weight);
    void onHeightFinal(int height);
    void onNIBPFinal(int sys, int dia);

private:
    bool ensurePatientSaved();
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
};
