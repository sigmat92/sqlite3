#include "visionservice.h"
#include <QDebug>
/* ==========================================================
 * Constructor
 * ==========================================================*/

VisionService::VisionService(QObject *parent)
    : QObject(parent)
{
    loadNearChart();
}

/* ==========================================================
 * Mode Selection
 * ==========================================================*/

void VisionService::setNearMode()
{
    m_mode = Mode::Near;
    loadNearChart();
}

void VisionService::setFarMode()
{
    m_mode = Mode::Far;
    loadFarChart();
}

/* ==========================================================
 * Load Near Vision Chart
 * ==========================================================*/

void VisionService::loadNearChart()
{
    m_chart.clear();

    m_chart.append({
        "E",
        90,
        "N18"
    });

    m_chart.append({
        "F P",
        78,
        "N12"
    });

    m_chart.append({
        "D E F",
        66,
        "N10"
    });

    m_chart.append({
        "P T O",
        54,
        "N8"
    });

    m_chart.append({
        "N H K",
        42,
        "N6"
    });
}

/* ==========================================================
 * Load Far Vision Chart
 * ==========================================================*/

void VisionService::loadFarChart()
{
    m_chart.clear();

    m_chart.append({
        "E",
        110,
        "6/60"
    });

    m_chart.append({
        "F P",
        92,
        "6/36"
    });

    m_chart.append({
        "T O Z",
        76,
        "6/24"
    });

    m_chart.append({
        "L P E D",
        62,
        "6/18"
    });

    m_chart.append({
        "P E C F D",
        50,
        "6/12"
    });

    m_chart.append({
        "E D F C Z P",
        40,
        "6/9"
    });

    m_chart.append({
        "F E P O D T",
        32,
        "6/6"
    });
}

/* ==========================================================
 * Start Test
 * ==========================================================*/

void VisionService::startTest()
{
    m_currentLevel = 0;

    m_lastSuccessfulResult.clear();

    if (m_chart.isEmpty())
        return;

    emit nextLevel(
        m_chart[0].letters,
        m_chart[0].fontSize);
}

/* ==========================================================
 * User Answer
 * ==========================================================*/

void VisionService::submitAnswer(bool correct)
{
    
    if (m_chart.isEmpty())
        return;

    if (correct)
    {
        /*
         * Store latest successful level
         */
        m_lastSuccessfulResult =
                m_chart[m_currentLevel].result;

        ++m_currentLevel;

        /*
         * Finished whole chart
         */
        if (m_currentLevel >= m_chart.size())
        {
            qDebug() << "[VISION] Test completed:" << m_lastSuccessfulResult;
            emit testCompleted(
                    m_lastSuccessfulResult);
                //qDebug() << "[VISION] Test completed:" << m_lastSuccessfulResult;

            return;
        }

        emit nextLevel(
                m_chart[m_currentLevel].letters,
                m_chart[m_currentLevel].fontSize);
        //qDebug() << "[VISION] Test completed:" << m_lastSuccessfulResult;    
        return;
    }

    /*
     * Failed current level.
     * Report previous successful level.
     */

    if (m_lastSuccessfulResult.isEmpty())
    {
        /*
         * Couldn't even read first line.
         */
        emit testCompleted(
                "Below "
                + m_chart.first().result);
    }
    else
    {
        emit testCompleted(
                m_lastSuccessfulResult);
    }
}