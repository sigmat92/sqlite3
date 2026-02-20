#include "visiontestcontroller.h"
#include "view/visiontestview.h"

VisionTestController::VisionTestController(
        VisionTestView* v, QObject* parent)
    : QObject(parent), view(v)
{
    connect(view, &VisionTestView::startRequested,
            this, &VisionTestController::onStart);
    connect(view, &VisionTestView::okPressed,
            this, &VisionTestController::onOk);
    connect(view, &VisionTestView::cantSeePressed,
            this, &VisionTestController::onCantSee);
    connect(view, &VisionTestView::backPressed,
            this, &VisionTestController::onBack);
}

void VisionTestController::onStart()
{
    index = 0;
    view->setTestText(testSequence[index]);
}

void VisionTestController::onOk()
{
    index++;
    if (index >= testSequence.size()) {
        view->setTestText("TEST PASSED");
    } else {
        view->setTestText(testSequence[index]);
    }
}

void VisionTestController::onCantSee()
{
    view->setTestText("TEST FAILED");
}

void VisionTestController::onBack()
{
    view->close();
}

