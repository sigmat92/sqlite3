#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <QObject>

class InputService;

class InputController : public QObject
{
    Q_OBJECT

public:
    explicit InputController(InputService* service,
                             QObject* parent = nullptr);

private slots:
    void onFocusNext();
    void onFocusPrevious();
    void onActivate();
};

#endif // INPUTCONTROLLER_H
