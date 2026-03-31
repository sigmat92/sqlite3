#include "printview.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

PrintView::PrintView(QWidget *parent)
    : BaseView("", parent)
{
    setStyleSheet("background:white;");

    QVBoxLayout *layout = new QVBoxLayout(m_contentWidget);

    /* ---------------- HEADER ---------------- */

    QLabel *header = new QLabel("Patient Report : ");
    header->setAlignment(Qt::AlignCenter);

    header->setStyleSheet(
        "background:#0d47a1;"
        "color:white;"
        "font-size:28px;"
        "font-weight:bold;"
        "border-radius:8px;"
    );

    layout->addWidget(header);

    /* ---------------- STATUS ---------------- */

    statusLabel = new QLabel("Patients Details");
    statusLabel->setAlignment(Qt::AlignCenter);

    statusLabel->setStyleSheet(
        "background:#bbdefb;"
        "font-size:22px;"
        "font-weight:bold;"
        "border-radius:8px;"
    );

    layout->addWidget(statusLabel);

    /* ---------------- PATIENT PANEL ---------------- */

    QWidget *patientPanel = new QWidget;
    patientPanel->setStyleSheet(
        "background:#bbdefb;"
        "font-size:20px;"
        "border-radius:8px;"
    );

    QVBoxLayout *pLayout = new QVBoxLayout(patientPanel);

    patientInfoLabel = new QLabel("--");
    patientInfoLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    pLayout->addWidget(patientInfoLabel);

    layout->addWidget(patientPanel);

    /* ---------------- VITALS GRID ---------------- */
    vitalsLabel = new QLabel("Vitals Details");
    vitalsLabel->setAlignment(Qt::AlignCenter);

    QWidget *vitalsPanel = new QWidget;
    vitalsPanel->setStyleSheet(
        "background:#bbdefb;"
        "font-size:22px;"
        "border-radius:8px;"
    );
    //vitalsPanel->addWidget(vitalsLabel);

    QGridLayout *grid = new QGridLayout(vitalsPanel);

    tempLabel   = new QLabel("--");
    spo2Label   = new QLabel("--");
    nibpLabel   = new QLabel("--");
    weightLabel = new QLabel("--");
    heightLabel = new QLabel("--");
    bmiLabel    = new QLabel("--");

    grid->addWidget(new QLabel("Temperature"),0,0);
    grid->addWidget(tempLabel,0,1);
    grid->setRowStretch(0, 1);

    grid->addWidget(new QLabel("SpO2 / Pulse"),1,0);
    grid->addWidget(spo2Label,1,1);
    grid->setRowStretch(1, 1);

    grid->addWidget(new QLabel("NIBP"),2,0);
    grid->addWidget(nibpLabel,2,1);
    grid->setRowStretch(2, 1);

    grid->addWidget(new QLabel("Weight"),3,0);
    grid->addWidget(weightLabel,3,1);
    grid->setRowStretch(3, 1);

    grid->addWidget(new QLabel("Height"),4,0);
    grid->addWidget(heightLabel,4,1);
    grid->setRowStretch(4, 1);

    grid->addWidget(new QLabel("BMI"),5,0);
    grid->addWidget(bmiLabel,5,1);
    grid->setRowStretch(5, 1);

    layout->addWidget(vitalsPanel);

    /* ---------------- FOOTER ---------------- */

    QHBoxLayout *footer = new QHBoxLayout;

    QPushButton *allRecordsBtn = new QPushButton("All Records");
    QPushButton *printBtn = new QPushButton("Print");
    QPushButton *exitBtn  = new QPushButton("Exit");

    printBtn->setStyleSheet(
        "font-size:24px;"
        "background:#0d47a1;"
        "color:white;"
        "border-radius:5px;"
    );

    exitBtn->setStyleSheet(
        "font-size:24px;"
        "background:#455a64;"
        "color:white;"
        //"background:#b71c1c;"   // red for exit
        "border-radius:5px;"
    );

    allRecordsBtn->setStyleSheet(
        "font-size:24px;"
        "background:#1976d2;"
        "color:white;"
        "border-radius:5px;"
    );

    footer->addWidget(allRecordsBtn);

    footer->addWidget(printBtn);
    footer->addWidget(exitBtn);

    layout->addLayout(footer);

    connect(allRecordsBtn,&QPushButton::clicked,
            this,&PrintView::backRequested);

    connect(exitBtn, &QPushButton::clicked,
        this, &PrintView::exitRequested);


}

/* ================= SAFE DATA BINDING ================= */

void PrintView::setData(const QVariantMap& d)
{
    qDebug() << "PRINT DATA MAP:" << d;

    auto getDouble = [&](const QString& key) {
        return d.contains(key) && !d[key].isNull()
               ? d[key].toDouble()
               : -1.0;
    };

    auto getInt = [&](const QString& key) {
        return d.contains(key) && !d[key].isNull()
               ? d[key].toInt()
               : -1;
    };

    auto getStr = [&](const QString& key) {
        return d.contains(key) && !d[key].isNull()
               ? d[key].toString()
               : "--";
    };

    /* -------- Patient Info -------- */
    /*
    QString name   = getStr("name");
    QString mobile = getStr("mobile");
    QString gender = getStr("gender");

    patientInfoLabel->setText(
        QString("Name: %1\nMobile: %2\nGender: %3")
            .arg(name)
            .arg(mobile)
            .arg(gender)
    );
    */
    QString name   = getStr("name");
    QString mobile = getStr("mobile");
    QString gender = getStr("gender");
    int age        = getInt("age");

    patientInfoLabel->setText(
        QString("Name: %1\nAge: %2\nMobile: %3\nGender: %4")
            .arg(name)
            .arg(age > 0 ? QString::number(age) : "--")
            .arg(mobile)
            .arg(gender)
    );
    /* -------- Vitals -------- */

    double temp = getDouble("temperature");
    int spo2    = getInt("spo2");
    int pulse   = getInt("pulse");
    int sys     = getInt("sys");
    int dia     = getInt("dia");
    double weight = getDouble("weight");
    double height = getDouble("height");

    tempLabel->setText(temp > 0 ? QString::number(temp) + " F" : "--");

    spo2Label->setText(
        (spo2 > 0 && pulse > 0)
        ? QString("%1 / %2").arg(spo2).arg(pulse)
        : "--"
    );

    nibpLabel->setText(
        (sys > 0 && dia > 0)
        ? QString("%1 / %2").arg(sys).arg(dia)
        : "--"
    );

    weightLabel->setText(weight > 0 ? QString::number(weight) + " kg" : "--");
    heightLabel->setText(height > 0 ? QString::number(height) + " cm" : "--");

    /* -------- BMI -------- */

    if(height > 0 && weight > 0)
    {
        double h = height / 100.0;
        double bmi = weight / (h*h);

        bmiLabel->setText(QString::number(bmi,'f',1));
    }
    else
    {
        bmiLabel->setText("--");
    }
}