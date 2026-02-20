#include "inputservice.h"

InputService::InputService(QObject* parent)
    : QObject(parent)
{}

void InputService::onRotatedLeft()
{
    emit focusPrevious();
}

void InputService::onRotatedRight()
{
    emit focusNext();
}

void InputService::onPressed()
{
    emit activate();
}

