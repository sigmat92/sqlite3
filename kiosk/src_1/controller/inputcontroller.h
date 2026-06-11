#pragma once
#include <QObject>

class InputService;

class InputController : public QObject
{
    Q_OBJECT
public:
    explicit InputController(InputService* service,
                             QObject* parent = nullptr);
};

