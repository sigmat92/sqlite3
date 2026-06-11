#include "visionservice.h"

VisionService::VisionService(QObject* parent)
    : QObject(parent)
{
    // Simulated near vision levels (big → small)
    levels = {
        "C S",
        "D E F",
        "P T O",
        "Z F L",
        "N H K"
    };
}

void VisionService::startTest()
{
    currentLevel = 0;

    if (!levels.empty())
        emit nextSymbol(levels[currentLevel]);
}

void VisionService::submitAnswer(bool correct)
{
    if (correct)
    {
        currentLevel++;

        if (currentLevel < levels.size())
        {
            emit nextSymbol(levels[currentLevel]);
        }
        else
        {
            emit testCompleted("Excellent Vision");
        }
    }
    else
    {
        QString result;

        if (currentLevel <= 1)
            result = "Poor Vision";
        else if (currentLevel == 2)
            result = "Average Vision";
        else
            result = "Good Vision";

        emit testCompleted(result);
    }
}
/*
#include "visionservice.h"
#include <QDebug>

VisionService::VisionService(QObject* parent)
    : QObject(parent)
{
    m_symbols = {"E_UP", "E_DOWN", "E_LEFT", "E_RIGHT"};
}

void VisionService::startTest()
{
    m_index = 0;
    m_correct = 0;

    emit showSymbol(m_symbols[m_index]);
}

void VisionService::submitAnswer(const QString& answer)
{
    QString symbol = m_symbols[m_index];
    QString correct = expectedAnswer(symbol);

    if (answer == correct)
        m_correct++;

    m_index++;

    if (m_index >= m_symbols.size())
    {
        QString result = (m_correct >= 3) ? "6/6" : "6/9";
        emit testFinished(result);
        return;
    }

    emit showSymbol(m_symbols[m_index]);
}

QString VisionService::expectedAnswer(const QString& symbol)
{
    if (symbol == "E_UP") return "UP";
    if (symbol == "E_DOWN") return "DOWN";
    if (symbol == "E_LEFT") return "LEFT";
    if (symbol == "E_RIGHT") return "RIGHT";
    return "";
}
*/