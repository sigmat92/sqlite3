#include <QApplication>
#include "VitalModel.h"
#include "MainWindow.h"
#include "VitalController.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    VitalModel model;
    MainWindow w;
    VitalController controller(&model, &w);

    //w.show();
    w.showFullScreen();
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&](){ model.updateData(); });
    timer.start(200);

    return a.exec();
}

