#pragma once

#include <QObject>
#include <QStackedWidget>
#include <QMap>
#include <QVector>
#include <QHash>

class QWidget;

struct WidgetNavigation
{
    QVector<QWidget*> widgets;
    int currentIndex = 0;
};
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

    // Register focusable widgets for a screen
    //void registerWidgets(Screen screen,
    //                 const QVector<QWidget*>& widgets);

    // Rotary navigation


    void registerWidgets(Screen screen,
                         const QVector<QWidget*>& widgets);

    void focusNext();

    void focusPrevious();

    void activate();

private:
    QStackedWidget* m_stack;
    QMap<Screen, QWidget*> m_screens;
    QVector<Screen> m_history;

    QHash<Screen, WidgetNavigation> m_widgetMap;
    
    Screen m_currentScreen = Screen::Home;
};