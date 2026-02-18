
#pragma once

#include <QObject>
#include <QSet>
#include <QHash>
#include <QTimer>

class VitalsService : public QObject
{
    Q_OBJECT
public:
    explicit VitalsService(QObject* parent = nullptr);

    void startMeasurement();

signals:
    // Validated outputs
    void temperatureReady(double value, char unit);
    void spo2Ready(int spo2, int pulse);
    void weightReady(double weight);
    void heightReady(int height);
    void nibpReady(int sys, int dia, int map);

    // Busy + missing
    void sensorBusy(const QString& name, bool busy);
    void sensorMissing(const QString& name);

    void measurementFinished();

public slots:
    // Raw data from protocol layer
    void onTemperatureRaw(double value, char unit);
    void onSpO2Raw(int spo2, int pulse);
    void onWeightRaw(double weight);
    void onHeightRaw(int height);
    void onNibpRaw(int sys, int dia, int map);

private:
    void markComplete(const QString& name);
    void startTimeout(const QString& name);
    void checkCompletion();

    QSet<QString> m_expected;
    QSet<QString> m_completed;
    QHash<QString, QTimer*> m_timers;
};

/*
#include <QTimer>
#include <QSet>

class VitalsService : public QObject
{
    Q_OBJECT
public:
    explicit VitalsService(QObject* parent = nullptr);

    void startMeasurement();
    void stopMeasurement();

signals:
    // Valid data
    void temperatureReady(double value, char unit);
    void spo2Ready(int spo2, int pulse);
    void weightReady(double weight);
    void heightReady(int height);
    void nibpReady(int sys, int dia, int map);

    // Sensor state
    void sensorMissing(const QString& sensorName);

    // Busy control
    void sensorBusy(const QString& sensorName, bool busy);

    // Lifecycle
    void measurementFinished();

public slots:
    void onTemperatureRaw(double value, char unit);
    void onSpO2Raw(int spo2, int pulse);

private:
    void startSensorTimeout(const QString& name);
    void markSensorComplete(const QString& name);
    void checkCompletion();

    QSet<QString> m_expectedSensors;
    QSet<QString> m_completedSensors;

    QHash<QString, QTimer*> m_timeoutTimers;
};
*/
/*
#pragma once
#include <QObject>

class VitalsService : public QObject
{
    Q_OBJECT
public:
    explicit VitalsService(QObject* parent = nullptr);

    // lifecycle
    void startMeasurement();
    void stopMeasurement();

signals:
    // clean data for model
    void temperatureReady(double value, char unit);
    void spo2Ready(int spo2, int pulse);
    void weightReady(double weight);
    void heightReady(int height);
    void nibpReady(int sys, int dia, int map);

    // lifecycle
    void measurementFinished();

public slots:
    // raw input from UART / parser
    void onTemperatureRaw(double value, char unit);
    void onSpO2Raw(int spo2, int pulse);
    void onWeightRaw(double weight);
    void onHeightRaw(int height);
    void onNibpRaw(int sys, int dia, int map);

private:
    bool tempOk{false};
    bool spo2Ok{false};
    bool weightOk{false};
    bool heightOk{false};
    bool nibpOk{false};

    void checkCompletion();
};
*/
