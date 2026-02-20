#include "metriccard.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

MetricCard::MetricCard(const QString& title, QWidget* parent)
    : QWidget(parent)
{
        
    setStyleSheet("background:#e1f5fe; border-radius:8px;");

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);

    QLabel* titleLabel = new QLabel(title);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-weight:bold;");

    valueLabel = new QLabel("--");
    valueLabel->setAlignment(Qt::AlignCenter);
    valueLabel->setStyleSheet("font-size:22px; font-weight:bold;");

    startBtn = new QPushButton("Start");
    startBtn->setMinimumHeight(36);
    startBtn->setStyleSheet("background:#0d47a1; color:white;");

    connect(startBtn, &QPushButton::clicked,
            this, &MetricCard::startRequested);

    layout->addWidget(titleLabel);
    layout->addStretch();
    layout->addWidget(valueLabel);
    layout->addWidget(startBtn);
}

void MetricCard::setValue(const QString& value)
{
    valueLabel->setText(value);
}

void MetricCard::setBusy(bool busy)
{
    startBtn->setEnabled(!busy);
    startBtn->setText(busy ? "Measuring..." : "Start");
}

