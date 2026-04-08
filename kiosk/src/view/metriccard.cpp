#include "metriccard.h"

#include <QVBoxLayout>

MetricCard::MetricCard(const QString &title, QWidget *parent)
    : QWidget(parent)
{
    setObjectName("metricCard");
    /*
    setStyleSheet(
        "font-size:24px;"
        "background:#e1f5fe;"
        "font-weight:bold;"
        "border-radius: 10px;"
        "color:#555;"
    );
    */
setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//setMinimumWidth(200);
//setMaximumWidth(250);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setObjectName("metricLayout");
    titleLabel = new QLabel(title);
    titleLabel->setObjectName("metricTitle");
    titleLabel->setAlignment(Qt::AlignCenter);

    valueLabel = new QLabel("--");
    valueLabel->setObjectName("metricValue");
    valueLabel->setAlignment(Qt::AlignCenter);

    startButton = new QPushButton("Start");
    startButton->setObjectName("metricStartButton");
    /*
    startButton->setStyleSheet(
        "font-size:24px;"
        "font-weight:bold;"
        "background:#0288d1;"
        "color:white;"
        "border-radius: 5px;"
    );
    */
    layout->addWidget(titleLabel);
    //layout->addStretch();
    layout->addWidget(valueLabel);
    //layout->addStretch();
    layout->addWidget(startButton);

    connect(startButton,&QPushButton::clicked,
            this,&MetricCard::startRequested);
}

void MetricCard::setValue(const QString &value)
{
    valueLabel->setText(value);
}

void MetricCard::setBusy(bool busy)
{
    if(busy)
        valueLabel->setText("...");
}
