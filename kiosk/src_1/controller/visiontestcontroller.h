#pragma once
#include <QObject>

class VisionTestView;
class VisionService;

class VisionTestController : public QObject
{
    Q_OBJECT
public:
    explicit VisionTestController(VisionTestView *view,
                                  VisionService *service,
                                  QObject *parent = nullptr);

private slots:
    //void startLeftTest();
    //void startRightTest();
    void goBack();
    //void exitRequested();

private:
    VisionTestView *m_view;
    VisionService *m_service;
};