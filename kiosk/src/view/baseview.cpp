#include "baseview.h"
#include <QTimer>
#include <QProcess>

BaseView::BaseView(const QString &title, QWidget *parent)
    : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout(this);
    //m_mainLayout->setMargin(0);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    QWidget *header = createHeader(title);
    m_contentWidget = new QWidget;
    QWidget *footer = createFooter();

    m_mainLayout->addWidget(header);
    m_mainLayout->addWidget(m_contentWidget);
    m_mainLayout->addWidget(footer);

    startClock();
}

QWidget* BaseView::createHeader(const QString &title)
{
    QWidget *header = new QWidget;
    header->setStyleSheet("background-color: black; color: white;");
    //header->setFixedHeight(70);

    QHBoxLayout *layout = new QHBoxLayout(header);

    QLabel *logo = new QLabel("metsl");
    logo->setStyleSheet("font-size: 24px; font-weight: bold;");

    QLabel *pageTitle = new QLabel(title);
    pageTitle->setStyleSheet("font-size: 24px;");

    m_dateTimeLabel = new QLabel;


    m_dateTimeLabel->setStyleSheet(
        "color: #DDDDDD;"
        "font-size: 24px;"
        "font-weight: bold;"
    );

    //m_statusIndicator = new QLabel;
    //m_statusIndicator->setFixedSize(20,20);
    //m_statusIndicator->setStyleSheet(
    //    "background-color: red; border-radius: 24px;"
    //);

    auto* powerBtn = new QPushButton("Stop");
    
    powerBtn->setObjectName("powerButton");
    powerBtn->setStyleSheet(
        "color: #DDDDDD;"
        "font-size: 24px;"
        "font-weight: bold;"
        "border-radius: 15px;"
    );

    connect(powerBtn, &QPushButton::clicked, this, [this]() {
    //status->setText("Test Status: Shutting Down...");
    QProcess::startDetached("poweroff");
    });

    layout->addWidget(logo);
    layout->addSpacing(30);
    layout->addWidget(pageTitle);
    layout->addStretch();
    layout->addWidget(m_dateTimeLabel);
    layout->addSpacing(20);
    //layout->addWidget(m_statusIndicator);
    layout->addWidget(powerBtn);
    return header;
}

QWidget* BaseView::createFooter()
{
    QWidget *footer = new QWidget;
    footer->setStyleSheet("background-color: black; color: white;");
    //footer->setFixedHeight(50);

    QHBoxLayout *layout = new QHBoxLayout(footer);
    QLabel *version = new QLabel("Care Nest Mini ");
    version->setStyleSheet("font-size: 24px;");
    QLabel *versionLabel = new QLabel("v1.0.0");
    versionLabel->setStyleSheet("font-size: 24px;");
    layout->addWidget(version);
    layout->addStretch();
    layout->addWidget(versionLabel);
    //layout->addStretch();

    return footer;
}

void BaseView::startClock()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this](){
        m_dateTimeLabel->setText(
            QDateTime::currentDateTime()
                .toString("dd-MM-yyyy   hh:mm:ss"));
    });
    timer->start(1000);
}
