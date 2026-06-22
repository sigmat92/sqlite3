#ifndef VISIONSERVICE_H
#define VISIONSERVICE_H

#include <QObject>
#include <QString>
#include <QVector>

/*
 * Vision Test Service
 *
 * Handles:
 *  - Near vision
 *  - Far vision
 *  - Test progression
 *  - Font scaling
 *  - Final result
 *
 * No UI code.
 */

class VisionService : public QObject
{
    Q_OBJECT

public:

    explicit VisionService(QObject *parent = nullptr);

    enum class Mode
    {
        Near,
        Far
    };

    struct VisionLevel
    {
        QString letters;

        int fontSize;

        QString result;
    };

public slots:

    void setNearMode();

    void setFarMode();

    void startTest();

    void submitAnswer(bool correct);

signals:

    /*
     * Update screen
     */
    void nextLevel(
            QString letters,
            int fontSize);

    /*
     * Final result
     */
    void testCompleted(
            QString result);

private:

    void loadNearChart();

    void loadFarChart();

private:

    QVector<VisionLevel> m_chart;

    int m_currentLevel = 0;

    Mode m_mode = Mode::Near;

    QString m_lastSuccessfulResult;
};

#endif