#include "VitalController.h"
#include "MainWindow.h"

VitalController::VitalController(VitalModel *model, MainWindow *view, QObject *parent)
    : QObject(parent), model(model), view(view)
{
    // Example: connect model update signal to controller slot
    connect(model, &VitalModel::dataUpdated, this, &VitalController::refreshView);
}

void VitalController::refreshView(const VitalData &data)
{
    // Update readings via public setters
    view->setECG(data.ecg);
    view->setRESP(data.resp);
    view->setSPO2(data.spo2);
    view->setBP(data.bpSys, data.bpDia);

    // Footer text (no alarm member)
    view->setFooterText("Status: Monitoring");

    // Add waveform points
    view->ecgWidget->addValue(data.ecg);
    view->respWidget->addValue(data.resp);
    view->spo2Widget->addValue(data.spo2 / 100.0);
    view->bpWidget->addValue((data.bpSys - 80) / 60.0); // scaled
}


/*
void VitalController::refreshView(const VitalData &data)
{
    // Use public setters instead of private QLabel access
    view->setECG(data.ecg);
    view->setRESP(data.resp);
    view->setSPO2(data.spo2);
    view->setBP(data.bpSys, data.bpDia);

    QString alarm = data.alarm ? "ON" : "None";
    view->setFooterText("Status: Monitoring | Alarm: " + alarm);

    // Add waveform points
    view->ecgWidget->addValue(data.ecg);
    view->respWidget->addValue(data.resp);
    view->spo2Widget->addValue(data.spo2 / 100.0);
    view->bpWidget->addValue((data.bpSys - 80) / 60.0); // scaled for display
}
*/
