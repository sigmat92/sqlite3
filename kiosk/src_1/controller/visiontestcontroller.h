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