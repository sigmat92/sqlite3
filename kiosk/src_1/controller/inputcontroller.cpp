
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
void HomeController::onVitalsUpdated(int spo2, int pulse)
{
    // Update UI
    m_view->setSpO2(spo2, pulse);

    // Optional: persist to DB
    if (m_repo) {
        m_repo->saveVitals(
            m_session->currentPatientId(),
            spo2,
            pulse
        );
    }
}

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
