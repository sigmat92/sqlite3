#include "controller/visiontestcontroller.h"
#include "view/visiontestview.h"
#include "service/visionservice.h"
#include "model/vitalsmodel.h"
#include <QDebug>

/* ==========================================================
 * Constructor
 * ==========================================================*/

VisionTestController::VisionTestController(
        VisionTestView *view,
        VisionService *service,
        VitalsModel *model,
        QObject *parent)
    : QObject(parent),
      m_view(view),
      m_service(service),
      m_vitalsModel(model)
{
    /* =====================================================
     * MODE SELECTION
     * =====================================================*/

    connect(m_view,
            &VisionTestView::nearModeSelected,
            m_service,
            &VisionService::setNearMode);

    connect(m_view,
            &VisionTestView::farModeSelected,
            m_service,
            &VisionService::setFarMode);

    /* =====================================================
     * START TEST
     * =====================================================*/

    connect(m_view,
            &VisionTestView::startRequested,
            this,
            [this]()
    {
        /*
         * Ensure service is in the correct mode before starting.
         */

        if (m_view->isNearMode())
            m_service->setNearMode();
        else
            m_service->setFarMode();

        m_service->startTest();
    });

    /* =====================================================
     * USER ANSWERS
     * =====================================================*/

    connect(m_view,
            &VisionTestView::answerSelected,
            this,
            [this](const QString &answer)
    {
        m_service->submitAnswer(answer == "PASS");
    });

    /* =====================================================
     * DISPLAY NEXT LEVEL
     * =====================================================*/

    connect(m_service,
            &VisionService::nextLevel,
            m_view,
            &VisionTestView::displayLevel);

    /* =====================================================
     * DISPLAY FINAL RESULT
     * =====================================================*/

    //connect(m_service,
    //        &VisionService::testCompleted,
    //        m_view,
    //        &VisionTestView::showResult);
    //}


connect(m_service,
        &VisionService::testCompleted,
        this,
        [this](QString result)
{
    if (m_view->isNearMode())
    {
        qDebug() << "[VISION CONTROLLER]"
         << "Result =" << result
         << "Near mode =" << m_view->isNearMode();
        m_vitalsModel->setNearVision(result);
    }
    else
    {
        qDebug() << "[VISION CONTROLLER]"
         << "Result =" << result
         << "Near mode =" << m_view->isNearMode();
        m_vitalsModel->setFarVision(result);
    }

    m_view->showResult(result);
});
}