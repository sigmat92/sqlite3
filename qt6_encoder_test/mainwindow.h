#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "rotaryhandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateCount(int newCount);
    void updateSwitch(bool pressed);

private:
    Ui::MainWindow *ui;
    RotaryHandler *rotary;
    QThread workerThread;
    int counter;
};

#endif // MAINWINDOW_H

