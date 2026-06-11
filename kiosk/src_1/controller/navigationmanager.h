#pragma once

#include <QObject>
#include <QStackedWidget>
#include <QMap>
#include <QVector>

enum class Screen
{
    Home,
    Settings,
    Print,
    Records,
    Vision
};

class NavigationManager : public QObject
{
    Q_OBJECT

public:
    explicit NavigationManager(QStackedWidget* stack, QObject* parent = nullptr);

    void registerScreen(Screen screen, QWidget* widget);

    void goTo(Screen screen);
    void goBack();

private:
    QStackedWidget* m_stack;
    QMap<Screen, QWidget*> m_screens;
    QVector<Screen> m_history;
};