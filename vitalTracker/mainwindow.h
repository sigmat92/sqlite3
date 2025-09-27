#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vitalmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateVitals(VitalModel *model);

private slots:
    void startPressed();
    void mutePressed();
    void timestampPressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

