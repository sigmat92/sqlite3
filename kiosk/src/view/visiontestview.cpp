#include "visiontestview.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QFont>

/* ==========================================================
 * Constructor
 * ==========================================================*/

VisionTestView::VisionTestView(QWidget *parent)
    : BaseView("Vision Test", parent)
{
    auto *layout = new QVBoxLayout(m_contentWidget);

    layout->setSpacing(20);

    /* =====================================================
     * MODE BUTTONS
     * =====================================================*/

    QWidget *modeWidget = new QWidget;

    QHBoxLayout *modeLayout =
            new QHBoxLayout(modeWidget);

    modeLayout->setSpacing(20);

    farButton = new QPushButton("Far Vision");

    nearButton = new QPushButton("Near Vision");

    //farButton->setMinimumHeight(60);
    //nearButton->setMinimumHeight(60);

    farButton->setSizePolicy(
                QSizePolicy::Expanding,
                QSizePolicy::Preferred);

    nearButton->setSizePolicy(
                QSizePolicy::Expanding,
                QSizePolicy::Preferred);

    modeLayout->addWidget(farButton);
    modeLayout->addWidget(nearButton);

    layout->addWidget(modeWidget);

    connect(farButton,
            &QPushButton::clicked,
            this,
            &VisionTestView::onFarClicked);

    connect(nearButton,
            &QPushButton::clicked,
            this,
            &VisionTestView::onNearClicked);

    /* =====================================================
     * ADVICE
     * =====================================================*/

    adviceLabel =
            new QLabel(
                "Sit comfortably and read the letters.");

    adviceLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(adviceLabel);

    /* =====================================================
     * START
     * =====================================================*/

    startButton =
            new QPushButton("START");

    //startButton->setMinimumHeight(70);

    layout->addWidget(startButton);

    connect(startButton,
            &QPushButton::clicked,
            this,
            &VisionTestView::startRequested);

    /* =====================================================
     * LETTER PANEL
     * =====================================================*/

    QFrame *panel = new QFrame;

    panel->setFrameShape(QFrame::StyledPanel);

    QVBoxLayout *panelLayout =
            new QVBoxLayout(panel);

    symbolLabel = new QLabel("");

    symbolLabel->setAlignment(Qt::AlignCenter);

    symbolLabel->setMinimumHeight(350);

    QFont f;

    f.setBold(true);

    f.setPointSize(72);

    symbolLabel->setFont(f);

    panelLayout->addWidget(symbolLabel);

    layout->addWidget(panel);

    /* =====================================================
     * RESPONSE BUTTONS
     * =====================================================*/

    QWidget *responseWidget =
            new QWidget;

    QHBoxLayout *responseLayout =
            new QHBoxLayout(responseWidget);
            

    okButton =
            //new QPushButton("OK");
            new QPushButton("CAN SEE");

    cantSeeButton =
            new QPushButton("CANNOT SEE");

    //okButton->setMinimumHeight(70);

    //cantSeeButton->setMinimumHeight(70);

    okButton->setSizePolicy(
                QSizePolicy::Expanding,
                QSizePolicy::Preferred);

    cantSeeButton->setSizePolicy(
                QSizePolicy::Expanding,
                QSizePolicy::Preferred);

    responseLayout->addWidget(okButton);

    responseLayout->addWidget(cantSeeButton);

    layout->addWidget(responseWidget);

    connect(okButton,
            &QPushButton::clicked,
            this,
            [this]()
    {
        emit answerSelected("PASS");
    });

    connect(cantSeeButton,
            &QPushButton::clicked,
            this,
            [this]()
    {
        emit answerSelected("FAIL");
    });

    /* =====================================================
     * RESULT
     * =====================================================*/

    resultLabel =
            new QLabel("--");

    resultLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(resultLabel);

    /* =====================================================
     * BACK
     * =====================================================*/

    QPushButton *backButton =
            new QPushButton("BACK");

    //backButton->setMinimumHeight(60);

    layout->addWidget(backButton);

    connect(backButton,
            &QPushButton::clicked,
            this,
            &VisionTestView::exitRequested);

    updateModeButtons();
}

/* ==========================================================
 * Near/Far Selection
 * ==========================================================*/

void VisionTestView::onNearClicked()
{
    m_nearMode = true;

    updateModeButtons();

    emit nearModeSelected();
}

void VisionTestView::onFarClicked()
{
    m_nearMode = false;

    updateModeButtons();

    emit farModeSelected();
}

bool VisionTestView::isNearMode() const
{
    return m_nearMode;
}

/* ==========================================================
 * Button Highlight
 * ==========================================================*/

void VisionTestView::updateModeButtons()
{
    if(m_nearMode)
    {
        nearButton->setEnabled(false);
        farButton->setEnabled(true);

        adviceLabel->setText(
                    "Make sure you are approximately at 35-40 cm.");
    }
    else
    {
        nearButton->setEnabled(true);
        farButton->setEnabled(false);

        adviceLabel->setText(
                    "Stand approximately 6 metres from the display.");
    }
}

/* ==========================================================
 * Display Letters
 * ==========================================================*/

void VisionTestView::displayLevel(
        QString letters,
        int fontSize)
{
    QFont f = symbolLabel->font();

    f.setBold(true);

    f.setPointSize(fontSize);

    symbolLabel->setFont(f);

    symbolLabel->setText(letters);

    resultLabel->setText("--");
}

/* ==========================================================
 * Result
 * ==========================================================*/

void VisionTestView::showResult(QString result)
{
    resultLabel->setText(
                "Vision Result : " + result);

    symbolLabel->setText("✓");

    QFont f = symbolLabel->font();

    f.setPointSize(120);

    symbolLabel->setFont(f);
}