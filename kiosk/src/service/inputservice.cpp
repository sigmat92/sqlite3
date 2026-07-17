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

void InputService::onMutePressed()
{
    qDebug() << "InputService : MUTE";
    emit mute();
}

void InputService::onNibpPressed()
{
    qDebug() << "InputService : NIBP";
    emit nibp();
}

void InputService::onFreezePressed()
{
    qDebug() << "InputService : FREEZE";
    emit freeze();
}

void InputService::onPrintPressed()
{
    qDebug() << "InputService : PRINT";
    emit print();
}

void InputService::onMenuPressed()
{
    qDebug() << "InputService : MENU";
    emit menu();
}

