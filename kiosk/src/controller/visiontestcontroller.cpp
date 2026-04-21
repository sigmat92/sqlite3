#include "controller/visiontestcontroller.h"
#include "view/visiontestview.h"
#include "service/visionservice.h"

VisionTestController::VisionTestController(
    VisionTestView* view,
    VisionService* service,
    QObject* parent)
    : QObject(parent),
      m_view(view),
      m_service(service)
{
    /* -------- START -------- */
    connect(m_view, &VisionTestView::startRequested,
            m_service, &VisionService::startTest);

    /* -------- ANSWERS -------- */
    connect(m_view, &VisionTestView::answerSelected,
            this, [this](QString ans) {

        if (ans == "OK")
            m_service->submitAnswer(true);
        else
            m_service->submitAnswer(false);
    });

    /* -------- UPDATE SYMBOL -------- */
    connect(m_service, &VisionService::nextSymbol,
            m_view, &VisionTestView::displaySymbol);

    /* -------- RESULT -------- */
    connect(m_service, &VisionService::testCompleted,
            m_view, &VisionTestView::showResult);
}
