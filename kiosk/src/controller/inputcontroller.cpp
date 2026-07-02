#include "inputcontroller.h"
#include "service/inputservice.h"

#include <QDebug>

InputController::InputController(InputService *service,
                                 QObject *parent)
    : QObject(parent)
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
}

void InputController::onFocusNext()
{
    qDebug() << "InputController : Focus Next";
}

void InputController::onFocusPrevious()
{
    qDebug() << "InputController : Focus Previous";
}

void InputController::onActivate()
{
    qDebug() << "InputController : Activate";
}