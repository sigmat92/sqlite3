#include "visiontestview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

VisionTestView::VisionTestView(QWidget *parent)
    : BaseView("Vision Test", parent)
{
    setupUi();
}
void VisionTestView::setupUi()
{
    QVBoxLayout *main = new QVBoxLayout(m_contentWidget);
    main->setContentsMargins(40,40,40,40);
    main->setSpacing(20);

    // ===== Mode Selector =====
    QHBoxLayout *modeLayout = new QHBoxLayout;

    m_nearBtn = new QPushButton("Near Vision");
    m_farBtn  = new QPushButton("Far Vision");

    modeLayout->addWidget(m_nearBtn);
    modeLayout->addWidget(m_farBtn);

    main->addLayout(modeLayout);

    // ===== Instruction =====
    m_instruction = new QLabel("Stand at 36 cm distance");
    m_instruction->setAlignment(Qt::AlignCenter);
    m_instruction->setStyleSheet("font-size:18px; font-weight:bold;");
    main->addWidget(m_instruction);

    // ===== START BUTTON =====
    m_startBtn = new QPushButton("START");
    m_startBtn->setFixedHeight(60);
    main->addWidget(m_startBtn);

    // ===== TEST AREA =====
    m_testLabel = new QLabel("CS");
    m_testLabel->setAlignment(Qt::AlignCenter);
    m_testLabel->setMinimumHeight(250);
    m_testLabel->setStyleSheet(R"(
        background:white;
        font-size:40px;
        border-radius:10px;
    )");

    main->addWidget(m_testLabel);

    // ===== RESULT BUTTONS =====
    QHBoxLayout *resultLayout = new QHBoxLayout;

    m_failBtn = new QPushButton("CAN'T SEE");
    m_passBtn = new QPushButton("OK");

    m_failBtn->setStyleSheet("background:red;color:white;");
    m_passBtn->setStyleSheet("background:green;color:white;");

    resultLayout->addWidget(m_failBtn);
    resultLayout->addWidget(m_passBtn);

    main->addLayout(resultLayout);

    // ===== BACK BUTTON =====
    m_backBtn = new QPushButton("BACK");
    main->addWidget(m_backBtn);

    // ===== SIGNALS =====

    connect(m_backBtn, &QPushButton::clicked,
            this, &VisionTestView::exitRequested);

    connect(m_startBtn, &QPushButton::clicked,
            this, &VisionTestView::startRequested);

    connect(m_passBtn, &QPushButton::clicked,
            this, &VisionTestView::passRequested);

    connect(m_failBtn, &QPushButton::clicked,
            this, &VisionTestView::failRequested);

    connect(m_nearBtn, &QPushButton::clicked, this, [this]() {
        m_mode = "NEAR";
        m_instruction->setText("Stand at 36 cm distance");
        emit modeChanged("NEAR");
    });

    connect(m_farBtn, &QPushButton::clicked, this, [this]() {
        m_mode = "FAR";
        m_instruction->setText("Stand at 6 meters distance");
        emit modeChanged("FAR");
    });
}
/*
void VisionTestView::setupUi()
{
    QVBoxLayout *layout = new QVBoxLayout(m_contentWidget);
    layout->setContentsMargins(40,40,40,40);
    layout->setSpacing(30);

    m_leftBtn = new QPushButton("Start Left Eye Test");
    m_rightBtn = new QPushButton("Start Right Eye Test");
    m_backBtn = new QPushButton("Back");

    m_leftResult = new QLabel("--");
    m_rightResult = new QLabel("--");

    m_leftBtn->setStyleSheet("background:#1E4E9E;color:white;");
    m_rightBtn->setStyleSheet("background:#1E4E9E;color:white;");
    m_backBtn->setStyleSheet("background:#1E4E9E;color:white;");

    layout->addWidget(m_leftBtn);
    layout->addWidget(m_leftResult);
    layout->addSpacing(20);
    layout->addWidget(m_rightBtn);
    layout->addWidget(m_rightResult);
    layout->addSpacing(20);
    layout->addWidget(m_backBtn);

    connect(m_leftBtn, &QPushButton::clicked,
            this, &VisionTestView::leftStartRequested);

    connect(m_rightBtn, &QPushButton::clicked,
            this, &VisionTestView::rightStartRequested);

    connect(m_backBtn, &QPushButton::clicked,
            this, &VisionTestView::backRequested);
    
    connect(m_exitBtn, &QPushButton::clicked,
        this, &VisionTestView::exitRequested);
}
*/
void VisionTestView::setLeftResult(const QString &value)
{
    m_leftResult->setText(value);
}

void VisionTestView::setRightResult(const QString &value)
{
    m_rightResult->setText(value);
}