#pragma once
#include <QObject>

class InputService : public QObject
{
    Q_OBJECT
public:
    explicit InputService(QObject* parent = nullptr);

signals:
    void focusNext();
    void focusPrevious();
    void activate();

public slots:
    void onRotatedLeft();
    void onRotatedRight();
    void onPressed();
};

