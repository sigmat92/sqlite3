#include "mainwindow.h"
#include "vitalmodel.h"
#include "vitalcontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    VitalModel model;
    MainWindow w;
    VitalController controller(&model, &w);

    //w.show();
     w.showFullScreen();
    return a.exec();
}

