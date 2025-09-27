#include "vitalcontroller.h"

VitalController::VitalController(VitalModel *model, MainWindow *view, QObject *parent)
    : QObject(parent), m_model(model), m_view(view) {}

VitalController::~VitalController() {}

