#pragma once
#include <QObject>

class VisionTestView;
class VisionService;
class VitalsModel;

class VisionTestController : public QObject
{
    Q_OBJECT

public:
    VisionTestController(
        VisionTestView *view,
        VisionService *service,
        VitalsModel *model,
        QObject *parent = nullptr
    );

private:
    VisionTestView* m_view;
    VisionService* m_service;
    VitalsModel* m_vitalsModel;
};
/*
#pragma once
#include <QObject>

class VisionTestView;
class VisionService;

class VisionTestController : public QObject
{
    Q_OBJECT

public:
    VisionTestController(VisionTestView* view,
                         VisionService* service,
                         QObject* parent = nullptr);

private:
    VisionTestView* m_view;
    VisionService* m_service;
};
*/