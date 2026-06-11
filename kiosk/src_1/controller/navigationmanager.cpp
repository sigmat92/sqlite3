#include "navigationmanager.h"
#include <QDebug>

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