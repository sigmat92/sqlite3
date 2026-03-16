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

void VisionTestView::setLeftResult(const QString &value)
{
    m_leftResult->setText(value);
}

void VisionTestView::setRightResult(const QString &value)
{
    m_rightResult->setText(value);
}