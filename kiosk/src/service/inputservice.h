
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
    
    void onMutePressed();
    void onNibpPressed();
    void onFreezePressed();
    void onPrintPressed();
    void onMenuPressed();

signals:
    void focusNext();
    void focusPrevious();
    void activate();
    
    void mute();
    void nibp();
    void freeze();
    void print();
    void menu();
};


