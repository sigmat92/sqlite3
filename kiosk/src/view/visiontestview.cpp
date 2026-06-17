#include "visiontestview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

VisionTestView::VisionTestView(QWidget* parent)
    : BaseView("Vision Test", parent)
{
    auto *layout = new QVBoxLayout(m_contentWidget);

    /* ---------------- Far VISION TEST BUTTON ---------------- */

    QPushButton *farVisionTestBtn = new QPushButton("Far Vision Test");
    farVisionTestBtn->setObjectName("farVisionTestBtn");
    layout->addWidget(farVisionTestBtn);
    //connect(farVisionBtn,&QPushButton::clicked,
    //        this, &VisionTestView::farVisonTestRequested);

    /* ---------------- NEAR VISION TEST BUTTON ---------------- */

    QPushButton *nearVisionTestBtn = new QPushButton("Near Vision Test");
    nearVisionTestBtn->setObjectName("nearVisionTestBtn");
    layout->addWidget(nearVisionTestBtn);
    //connect(nearVisionBtn,&QPushButton::clicked,
    //        this, &VisionTestView::nearVisonTestRequested);

    /* ---------------- adviceLabel ---------------- */

    QLabel *adviceLabel = new QLabel("Place yourself at 36 cm distance from the Device");
    adviceLabel->setObjectName("adviceLabel");
    adviceLabel->setAlignment(Qt::AlignCenter);
    
    layout->addWidget(adviceLabel);

    /* ---------------- START BUTTON ---------------- */

    QPushButton *startBtn = new QPushButton("START");
    layout->addWidget(startBtn);
    connect(startBtn, &QPushButton::clicked,
            this, &VisionTestView::startRequested);

    /* ---------------- LETTER PANEL ---------------- */

    QWidget *visionPanel = new QWidget;

    QVBoxLayout *vLayout = new QVBoxLayout(visionPanel);

    symbolLabel = new QLabel("C S");
    symbolLabel->setAlignment(Qt::AlignCenter);

    visionPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    vLayout->addWidget(symbolLabel);

    layout->addWidget(visionPanel);

    /* ---------------- RESPONSE BUTTONS ---------------- */

    QWidget *responsePanel = new QWidget;
    QHBoxLayout *rLayout = new QHBoxLayout(responsePanel);

    QPushButton *cantSeeBtn = new QPushButton("CAN'T SEE");
    QPushButton *okBtn      = new QPushButton("OK");

    connect(cantSeeBtn, &QPushButton::clicked,
            [this]() { emit answerSelected("FAIL"); });

    connect(okBtn, &QPushButton::clicked,
            [this]() { emit answerSelected("PASS"); });

    rLayout->addWidget(cantSeeBtn);
    rLayout->addWidget(okBtn);

    layout->addWidget(responsePanel);

    /* ---------------- BACK BUTTON ---------------- */

    QPushButton *backBtn = new QPushButton("BACK");

    connect(backBtn, &QPushButton::clicked,
            this, &VisionTestView::exitRequested);

    layout->addWidget(backBtn);

    /* ---------------- RESULT ---------------- */

    resultLabel = new QLabel("--");
    resultLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(resultLabel);
}

void VisionTestView::showResult(QString result)
{
    statusLabel->setText("Test Status: Completed");

    if (symbolLabel)
        symbolLabel->setText("Done");

    if (resultLabel)
        resultLabel->setText("Result: " + result);
}
std::vector<QString> levels = {
    "C S",   // Large
    "D E F", // Medium
    "P T O", // Small
    "Z F L"  // Very small
};
void VisionTestView::displaySymbol(QString symbol)
{
    symbolLabel->setText(symbol);
}