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
   
    QVBoxLayout *layout = new QVBoxLayout(m_contentWidget);
    layout->setObjectName("contentLayout");

    /* ---------------- HEADER ---------------- */

    QLabel *header = new QLabel("Patient Report : ");
    header->setObjectName("header");
    header->setAlignment(Qt::AlignCenter);

    layout->addWidget(header);

    /* ---------------- STATUS ---------------- */

    /* ---------------- PATIENT PANEL ---------------- */

    QWidget *patientPanel = new QWidget;
    patientPanel->setObjectName("patientPanel");

    QVBoxLayout *pLayout = new QVBoxLayout(patientPanel);
    patientPanel->setObjectName("patientPanel");

    patientInfoLabel = new QLabel("--");
    patientInfoLabel->setObjectName("patientInfoLabel");
    patientInfoLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    pLayout->addWidget(patientInfoLabel);

    layout->addWidget(patientPanel);

    /* ---------------- VITALS GRID ---------------- */

    vitalsLabel = new QLabel("Vitals Details");
    vitalsLabel->setObjectName("vitalsLabel");
    vitalsLabel->setAlignment(Qt::AlignCenter);

    QWidget *vitalsPanel = new QWidget;
    vitalsPanel->setObjectName("vitalsPanel");

    QGridLayout *grid = new QGridLayout(vitalsPanel);
    grid->setObjectName("vitalsGrid");
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
    grid->setObjectName("footerGrid");
    QPushButton *allRecordsBtn = new QPushButton("All Records");
    allRecordsBtn->setObjectName("allRecordsBtn");
    QPushButton *printBtn = new QPushButton("Print");
    printBtn->setObjectName("printBtn");
    QPushButton *exitBtn  = new QPushButton("Exit");
    exitBtn->setObjectName("exitBtn");

    footer->addWidget(allRecordsBtn);

    footer->addWidget(printBtn);
    footer->addWidget(exitBtn);

    layout->addLayout(footer);

    connect(allRecordsBtn,&QPushButton::clicked,
            this,&PrintView::backRequested);

    connect(exitBtn, &QPushButton::clicked,
        this, &PrintView::exitRequested);

    connect(printBtn,&QPushButton::clicked,this,[this](){
        //qDebug() << "Print button clicked from print view, emitting startPrintRequested";

        //int sessionId = m_vitalsService->sessionId();
        //qDebug() << "Printing session in print view:" << sessionId;
        //qDebug() << "Emitting startPrintingRequested with sessionId:" << sessionId;
        emit startPrintingRequested();
        //emit startPrintingRequested(sessionId);
    });

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

    
    int sessionId = getInt("sessionId");
    QString name   = getStr("name");
    QString mobile = getStr("mobile");
    QString gender = getStr("gender");
    int age        = getInt("age");
    qDebug() << "printing in print view, sessionId:" << sessionId;
    patientInfoLabel->setText(
        QString("Name: %1\tAge: %2\tMobile: %3\tGender: %4")
            .arg(name)
            .arg(age > 0 ? QString::number(age) : "--")
            .arg(mobile)
            .arg(gender)
    );
    patientInfoLabel->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    
    /* -------- Vitals -------- */

    double temp = getDouble("temperature");
    int spo2    = getInt("spo2");
    int pulse   = getInt("pulse");
    int sys     = getInt("sys");
    int dia     = getInt("dia");
    double weight = getDouble("weight");
    //double height = getDouble("height");
    int height = getInt("height");
    
    tempLabel->setText(temp > 0 ? QString::number(temp) + " F" : "-- F");
    //tempLabel->setText(QString::number(temp) + " F" );
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

    weightLabel->setText(weight > 0 ? QString::number(weight) + " kg" : "-- kg");
    heightLabel->setText(height > 0 ? QString::number(height) + " cm" : "-- cm");

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