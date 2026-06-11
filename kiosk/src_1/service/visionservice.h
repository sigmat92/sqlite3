#pragma once
#include <QObject>
#include <vector>

class VisionService : public QObject
{
    Q_OBJECT

public:
    explicit VisionService(QObject* parent = nullptr);

    void startTest();
    void submitAnswer(bool correct);

signals:
    void nextSymbol(QString symbol);
    void testCompleted(QString result);

private:
    std::vector<QString> levels;
    int currentLevel = 0;
};
/*
#pragma once
#include <QObject>
#include <QStringList>

class VisionService : public QObject
{
    Q_OBJECT

public:
    explicit VisionService(QObject* parent = nullptr);

    void startTest();
    void submitAnswer(const QString& answer);

signals:
    void showSymbol(QString symbol);
    void testFinished(QString result);

private:
    QStringList m_symbols;
    int m_index = 0;
    int m_correct = 0;

    QString expectedAnswer(const QString& symbol);
};
*/

