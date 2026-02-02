
#include "inputcontroller.h"
#include "service/inputservice.h"

#include <QApplication>
#include <QCoreApplication>
#include <QKeyEvent>

InputController::InputController(InputService* service, QObject* parent)
    : QObject(parent)
{
    // Rotate right → Tab (next focus)
    connect(service, &InputService::focusNext, this, [] {
        if (QWidget* w = QApplication::focusWidget()) {
            QKeyEvent ev(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
            QCoreApplication::sendEvent(static_cast<QObject*>(w), &ev);
        }
    });

    // Rotate left → Shift+Tab (previous focus)
    connect(service, &InputService::focusPrevious, this, [] {
        if (QWidget* w = QApplication::focusWidget()) {
            QKeyEvent ev(QEvent::KeyPress,
                         Qt::Key_Tab,
                         Qt::ShiftModifier);
            QCoreApplication::sendEvent(static_cast<QObject*>(w), &ev);
        }
    });

    // Press → Enter (activate)
    connect(service, &InputService::activate, this, [] {
        if (QWidget* w = QApplication::focusWidget()) {
            QKeyEvent ev(QEvent::KeyPress,
                         Qt::Key_Return,
                         Qt::NoModifier);
            QCoreApplication::sendEvent(static_cast<QObject*>(w), &ev);
        }
    });
}
