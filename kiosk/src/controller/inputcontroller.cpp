#include "inputcontroller.h"

#include "controller/navigationmanager.h"
#include "view/homeview.h"
#include "service/inputservice.h"

#include <QDebug>

InputController::InputController(
        InputService* service,
        NavigationManager* navigation,
        HomeView* homeView,
        QObject* parent)
    : QObject(parent),
      m_service(service),
      m_navigation(navigation),
      m_homeView(homeView)

//InputController::InputController(InputService *service,
//                                 QObject *parent)
//    : QObject(parent)

{
    connect(service,
            &InputService::focusNext,
            this,
            &InputController::onFocusNext);

    connect(service,
            &InputService::focusPrevious,
            this,
            &InputController::onFocusPrevious);

    connect(service,
            &InputService::activate,
            this,
            &InputController::onActivate);

    connect(service,
        &InputService::mute,
        this,
        &InputController::onMute);

    connect(service,
            &InputService::nibp,
            this,
            &InputController::onNibp);

    connect(service,
            &InputService::freeze,
            this,
            &InputController::onFreeze);

    connect(service,
            &InputService::print,
            this,
            &InputController::onPrint);

    connect(service,
            &InputService::menu,
            this,
            &InputController::onMenu);
}

void InputController::onFocusNext()
{
    qDebug() << "InputController : Focus Next";

    if (m_navigation)
        m_navigation->focusNext();

    if (m_homeView)
        m_homeView->setStatus("Rotary -> Next");
}

void InputController::onFocusPrevious()
{
    qDebug() << "InputController : Focus Previous";

    if (m_navigation)
        m_navigation->focusPrevious();

    if (m_homeView)
        m_homeView->setStatus("Rotary -> Previous");
}

void InputController::onActivate()
{
    qDebug() << "InputController : Activate";

    if (m_navigation)
        m_navigation->activate();

    if (m_homeView)
        m_homeView->setStatus("Rotary -> Select");
}

void InputController::onMute()
{
    m_homeView->setStatus("Mute");
}

void InputController::onNibp()
{
    m_homeView->setStatus("NIBP");
}

void InputController::onFreeze()
{
    m_homeView->setStatus("Freeze");
}

void InputController::onPrint()
{
    m_homeView->setStatus("Print");
}

void InputController::onMenu()
{
    m_homeView->setStatus("Menu");
}