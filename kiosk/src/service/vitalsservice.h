#pragma once

#include <QObject>
#include <QTimer>

class VitalsRepository;

class VitalsService : public QObject
{
    Q_OBJECT

public:
    explicit VitalsService(QObject* parent = nullptr);

    // -------- SESSION --------
    void setSessionId(int id);
    int sessionId() const;   // FIXED (getter)

    void setRepository(VitalsRepository* repo);

    // -------- REQUESTS --------
    void requestTemperature();
    void requestSpo2();
    void requestNibp();
    void requestWeight();
    void requestHeight();
    void printResults(int sessionId);

signals:

    void sendCommand(const QByteArray&); // sensors
    void sendRaw(const QByteArray&);     // printer (thermal)
    
    // UI
    void temperatureReady(double, char);
    void spo2Ready(int, int);
    void nibpReady(int, int, int);
    void weightReady(double);
    void heightReady(int);

    // (optional but useful)
    void nibpPressure(int);

public slots:
    void onTemperature(double, char);
    void onSpo2(int, int);
    void onNibp(int, int, int);
    void onWeight(double);
    void onHeight(double);
    void onNibpPressure(int);

private:
    enum class State {
        Idle,
        Temp,
        Spo2,
        Nibp,
        Weight,
        Height
    };

    void setIdle();
    void startTimeout();

private:
    State state = State::Idle;
    QTimer timeout;

    int m_sessionId = -1;   // private (correct)
    VitalsRepository* m_repo = nullptr;
};