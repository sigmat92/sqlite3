#include "navigationmanager.h"
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QComboBox>
#include <QWidget>
#include <QDebug>
#include "view/metriccard.h"

NavigationManager::NavigationManager(QStackedWidget* stack, QObject* parent)
    : QObject(parent), m_stack(stack)
{
}

void NavigationManager::registerScreen(Screen screen, QWidget* widget)
{
    if (!widget) return;

    m_screens[screen] = widget;
    m_stack->addWidget(widget);
}

void NavigationManager::goTo(Screen screen)
{
    if (!m_screens.contains(screen))
    {
        qDebug() << "Screen not registered!";
        return;
    }

    QWidget* w = m_screens[screen];

    if (m_stack->currentWidget())
    {
        // Save history
        for (auto it = m_screens.begin(); it != m_screens.end(); ++it)
        {
            if (it.value() == m_stack->currentWidget())
            {
                m_history.append(it.key());
                break;
            }
        }
    }

m_stack->setCurrentWidget(w);

//Rotary navigation: Reset current index for the new screen

m_currentScreen = screen;

auto it = m_widgetMap.find(screen);

if (it != m_widgetMap.end())
{
    if (!it->widgets.isEmpty())
    {
        it->currentIndex = 0;
        it->widgets.first()->setFocus(Qt::OtherFocusReason);
    }
}

    qDebug() << "Navigated to screen:" << static_cast<int>(screen);
}

void NavigationManager::goBack()
{
    if (m_history.isEmpty())
        return;

    Screen last = m_history.takeLast();

    if (m_screens.contains(last))
    {
        m_stack->setCurrentWidget(m_screens[last]);
        qDebug() << "Back to screen:" << static_cast<int>(last);
    }
}
//Rotary navigation

void NavigationManager::registerWidgets(
        Screen screen,
        const QVector<QWidget*>& widgets)
{
    WidgetNavigation nav;
    nav.widgets = widgets;
    nav.currentIndex = 0;

    m_widgetMap.insert(screen, nav);
}

void NavigationManager::focusNext()
{
    auto it = m_widgetMap.find(m_currentScreen);

    if (it == m_widgetMap.end())
        return;

    auto &nav = it.value();

    if (nav.widgets.isEmpty())
        return;

    int count = nav.widgets.size();

    for (int i = 0; i < count; ++i)
    {
        nav.currentIndex =
            (nav.currentIndex + 1) % count;

        QWidget *w =
            nav.widgets[nav.currentIndex];

        if (w &&
            w->isVisible() &&
            w->isEnabled())
        {
            w->setFocus();
            return;
        }
    }
}

void NavigationManager::focusPrevious()
{
    auto it = m_widgetMap.find(m_currentScreen);

    if (it == m_widgetMap.end())
        return;

    auto &nav = it.value();

    if (nav.widgets.isEmpty())
        return;

    int count = nav.widgets.size();
    for (int i = 0; i < count; ++i)
    {
        nav.currentIndex--;

        if (nav.currentIndex < 0)
            nav.currentIndex = count - 1;

        QWidget *w = nav.widgets[nav.currentIndex];

        if (w &&
            w->isVisible() &&
            w->isEnabled())
        {
            w->setFocus(Qt::OtherFocusReason);
            return;
        }
    }
}

void NavigationManager::activate()
{

    //QWidget *w =
    //nav.widgets[nav.currentIndex];
    auto it = m_widgetMap.find(m_currentScreen);

    if (it == m_widgetMap.end())
        return;

    auto& nav = it.value();

    if (nav.widgets.isEmpty())
        return;

    QWidget* w = nav.widgets[nav.currentIndex];

    if (auto button = qobject_cast<QPushButton*>(w))
    {
        button->click();
    }
    else if (auto radio = qobject_cast<QRadioButton*>(w))
    {
        radio->click();
    }
    else if (auto check = qobject_cast<QCheckBox*>(w))
    {
        check->toggle();
    }
    else if (auto combo = qobject_cast<QComboBox*>(w))
    {
        combo->showPopup();
    }
}