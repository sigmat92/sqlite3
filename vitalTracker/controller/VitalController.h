#pragma once
#include <QObject>
#include "VitalModel.h"
#include "MainWindow.h"

class VitalController : public QObject {
    Q_OBJECT
public:
    explicit VitalController(VitalModel* m, MainWindow* w, QObject* parent = nullptr);

private slots:
    void refreshView(const VitalData& data);

private:
    VitalModel* model;
    MainWindow* view;
};

