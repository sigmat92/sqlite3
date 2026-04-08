#include "visiontestview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

VisionTestView::VisionTestView(QWidget* parent)
    : BaseView("Near Vision Test", parent)
{
    auto *layout = new QVBoxLayout(m_contentWidget);

    /* ---------------- STATUS ---------------- */

    statusLabel = new QLabel("Put yourself at 36 cm distance");
    statusLabel->setAlignment(Qt::AlignCenter);
    // statusLabel->setMinimumHeight(50);
    /*
    statusLabel->setStyleSheet(
        "background:#bbdefb;"
        "font-size:24px;"
        "font-weight:bold;"
        "border-radius:8px;"
    );
    */
    layout->addWidget(statusLabel);

    /* ---------------- START BUTTON ---------------- */

    QPushButton *startBtn = new QPushButton("START");
/*
    startBtn->setStyleSheet(
        "font-size:32px;"
        "font-weight:bold;"
        "background:white;"
        "color:black;"
        "border-radius:10px;"
        "min-height:70px;"
    );
*/
    /*  
    startBtn->setStyleSheet(
        "font-size:28px;"
        "border-radius: 8px;"
        "font-weight:bold;"
        "background:#0d47a1;"
        "color:white;"
    );
    */
    connect(startBtn, &QPushButton::clicked,
            this, &VisionTestView::startRequested);

    layout->addWidget(startBtn);

    /* ---------------- LETTER PANEL ---------------- */

    QWidget *visionPanel = new QWidget;
    /*
    visionPanel->setStyleSheet(
        "background:white;"
        "border-radius:8px;"
    );
    */
    QVBoxLayout *vLayout = new QVBoxLayout(visionPanel);

    symbolLabel = new QLabel("C S");
    symbolLabel->setAlignment(Qt::AlignCenter);
    /*
    symbolLabel->setStyleSheet(
        "font-size:80px;"
        "font-weight:bold;"
        "color:black;"
    );
    */
    visionPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    vLayout->addWidget(symbolLabel);

    layout->addWidget(visionPanel);

    /* ---------------- RESPONSE BUTTONS ---------------- */

    QWidget *responsePanel = new QWidget;
    QHBoxLayout *rLayout = new QHBoxLayout(responsePanel);

    QPushButton *cantSeeBtn = new QPushButton("CAN'T SEE");
    QPushButton *okBtn      = new QPushButton("OK");
    /*
    cantSeeBtn->setStyleSheet(
        "font-size:28px;"
        "font-weight:bold;"
        "background:#e53935;"
        "color:white;"
        "border-radius:10px;"
        "min-height:70px;"
    );

    okBtn->setStyleSheet(
        "font-size:28px;"
        "font-weight:bold;"
        "background:#43a047;"
        "color:white;"
        "border-radius:10px;"
        "min-height:70px;"
    );
    */
    connect(cantSeeBtn, &QPushButton::clicked,
            [=]() { emit answerSelected("FAIL"); });

    connect(okBtn, &QPushButton::clicked,
            [=]() { emit answerSelected("PASS"); });

    rLayout->addWidget(cantSeeBtn);
    rLayout->addWidget(okBtn);

    layout->addWidget(responsePanel);

    /* ---------------- BACK BUTTON ---------------- */

    QPushButton *backBtn = new QPushButton("BACK");
    /*
    backBtn->setStyleSheet(
        "font-size:26px;"
        "background:white;"
        "border-radius:8px;"
        "min-height:60px;"
    );
    */
    /*
        backBtn->setStyleSheet(
        "font-size:28px;"
        "border-radius: 8px;"
        "font-weight:bold;"
        "background:#455a64;"
        "color:white;"
    );
    */
    connect(backBtn, &QPushButton::clicked,
            this, &VisionTestView::exitRequested);

    layout->addWidget(backBtn);

    /* ---------------- RESULT ---------------- */

    resultLabel = new QLabel("--");
    resultLabel->setAlignment(Qt::AlignCenter);
        /*
        resultLabel->setStyleSheet(
        "background:#bbdefb;"
        "font-size:24px;"
        "font-weight:bold;"
        "border-radius:8px;"
    );
        */
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