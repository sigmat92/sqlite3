#include "../controller/visiontestcontroller.h"
#include "../view/visiontestview.h"
#include "../service/visionservice.h"

VisionTestController::VisionTestController(
        VisionTestView *view,
        VisionService *service,
        QObject *parent)
    : QObject(parent),
      m_view(view),
      m_service(service)
{
    //connect(m_view, &VisionTestView::leftStartRequested,
    //        this, &VisionTestController::startLeftTest);

    //connect(m_view, &VisionTestView::rightStartRequested,
    //        this, &VisionTestController::startRightTest);

    connect(m_view, &VisionTestView::backRequested,
            this, &VisionTestController::goBack);
}
/*
void VisionTestController::startLeftTest()
{
    m_view->setEnabled(false);

    QString result = m_service->runLeftEyeTest();

    m_view->setLeftResult(result);
    m_view->setEnabled(true);
}

void VisionTestController::startRightTest()
{
    m_view->setEnabled(false);

    QString result = m_service->runRightEyeTest();

    m_view->setRightResult(result);
    m_view->setEnabled(true);
}
*/
void VisionTestController::goBack()
{
    // Navigation handled by parent stacked widget
    emit m_view->backRequested();
}

//void VisionTestController::exitRequested()
//{
//    emit m_view->exitRequested();
//}