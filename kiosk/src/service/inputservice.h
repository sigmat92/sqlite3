
#pragma once

#include <QObject>

class InputService : public QObject
{
    Q_OBJECT

public:
    explicit InputService(QObject *parent = nullptr);

public slots:
    void navigateNext();
    void navigatePrevious();
    void select();

signals:
    void focusNext();
    void focusPrevious();
    void activate();
};


