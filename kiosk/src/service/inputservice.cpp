#include "inputservice.h"
#include <QDebug>
InputService::InputService(QObject *parent)
    : QObject(parent)
{
}

void InputService::navigateNext()
{
    qDebug() << "InputService : NEXT";
    emit focusNext();
}

void InputService::navigatePrevious()
{
    qDebug() << "InputService : PREVIOUS";
    emit focusPrevious();
}

void InputService::select()
{
    qDebug() << "InputService : SELECT";
    emit activate();
}


