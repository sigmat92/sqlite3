#include "visiontestview.h"
#include "model/settingsmodel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

VisionTestView::VisionTestView(QWidget* parent)
    : QWidget(parent)
{
    resize(620, 340);
    setWindowTitle("Near Vision Test");
    setStyleSheet("background-color:#4fc3f7;");

    auto* root = new QVBoxLayout(this);
    root->setContentsMargins(30, 30, 30, 30);
    root->setSpacing(20);

    // Title
    QLabel* title = new QLabel("Near Vision Test");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size:28px; font-weight:bold;");
    root->addWidget(title);

    QLabel* instruction =
        new QLabel("Put Yourself on 36 cm Distance");
    instruction->setAlignment(Qt::AlignCenter);
    instruction->setStyleSheet("font-size:18px;");
    root->addWidget(instruction);

    // START button
    QPushButton* startBtn = new QPushButton("START");
    startBtn->setMinimumHeight(50);
    startBtn->setStyleSheet(
        "font-size:20px; background:#e0e0e0;");
    connect(startBtn, &QPushButton::clicked,
            this, &VisionTestView::startRequested);
    root->addWidget(startBtn, 0, Qt::AlignCenter);

    // Test display
    testLabel = new QLabel("--");
    testLabel->setAlignment(Qt::AlignCenter);
    testLabel->setMinimumHeight(200);
    testLabel->setStyleSheet(
        "background:white;"
        "font-size:48px;"
        "border-radius:6px;");
    root->addWidget(testLabel);

    // OK / CAN'T SEE buttons
    auto* btnRow = new QHBoxLayout;

    QPushButton* cantSee = new QPushButton("CAN'T SEE");
    cantSee->setMinimumHeight(50);
    cantSee->setStyleSheet(
        "background:#e53935; color:white; font-size:18px;");
    connect(cantSee, &QPushButton::clicked,
            this, &VisionTestView::cantSeePressed);

    QPushButton* ok = new QPushButton("OK");
    ok->setMinimumHeight(50);
    ok->setStyleSheet(
        "background:#43a047; color:white; font-size:18px;");
    connect(ok, &QPushButton::clicked,
            this, &VisionTestView::okPressed);

    btnRow->addWidget(cantSee);
    btnRow->addWidget(ok);
    root->addLayout(btnRow);

    // Back
    QPushButton* back = new QPushButton("BACK");
    back->setMinimumHeight(40);
    connect(back, &QPushButton::clicked,
            this, &VisionTestView::backPressed);
    root->addWidget(back, 0, Qt::AlignLeft);
}

void VisionTestView::setTestText(const QString& text)
{
    testLabel->setText(text);
}

