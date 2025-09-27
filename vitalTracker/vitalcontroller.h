#ifndef VITALCONTROLLER_H
#define VITALCONTROLLER_H

#include <QObject>
#include "vitalmodel.h"
#include "mainwindow.h"

class VitalController : public QObject
{
    Q_OBJECT
public:
    explicit VitalController(VitalModel *model, MainWindow *view, QObject *parent = nullptr);
    ~VitalController();

private:
    VitalModel *m_model;
    MainWindow *m_view;
};

#endif // VITALCONTROLLER_H

