#include "printview.h"
#include "service/healthmetricsservice.h"
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
    farVisionLabel = new QLabel("--");
    nearVisionLabel = new QLabel("--");
    bmiLabel    = new QLabel("--");
    bmiAnalysisLabel = new QLabel("--");
    bmrLabel = new QLabel("--");
    bsaLabel = new QLabel("--");

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

    grid->addWidget(new QLabel("BMI Analysis"),6,0);
    grid->addWidget(bmiAnalysisLabel,6,1);
    grid->setRowStretch(6, 1);

    grid->addWidget(new QLabel("BMR"),7,0);
    grid->addWidget(bmrLabel,7,1);
    grid->setRowStretch(7, 1);

    grid->addWidget(new QLabel("BSA"),8,0);
    grid->addWidget(bsaLabel,8,1);
    grid->setRowStretch(8, 1);

    grid->addWidget(new QLabel("Far Vision"),9,0);
    grid->addWidget(farVisionLabel,9,1);
    grid->setRowStretch(9, 1);

    grid->addWidget(new QLabel("Near Vision"),10,0);
    grid->addWidget(nearVisionLabel,10,1);
    grid->setRowStretch(10, 1);

    layout->addWidget(vitalsPanel);

    /* ---------------- FOOTER ---------------- */

    QHBoxLayout *footer = new QHBoxLayout;
    grid->setObjectName("footerGrid");
    QPushButton *allRecordsBtn = new QPushButton("All Records");
    allRecordsBtn->setObjectName("allRecordsBtn");
    QPushButton *printBtnThermal = new QPushButton("Thermal Print");
    QPushButton *printBtnNetwork = new QPushButton("Network Print");
    QPushButton *postVitalsBtn = new QPushButton("Post Vitals");
    postVitalsBtn->setObjectName("postVitalsBtn");
    printBtnThermal->setObjectName("printBtnThermal");
    printBtnNetwork->setObjectName("printBtnNetwork");
    QPushButton *exitBtn  = new QPushButton("Exit");
    exitBtn->setObjectName("exitBtn");

    footer->addWidget(allRecordsBtn);

    footer->addWidget(printBtnThermal);
    footer->addWidget(printBtnNetwork);
    footer->addWidget(postVitalsBtn);
    footer->addWidget(exitBtn);

    layout->addLayout(footer);

    connect(allRecordsBtn,&QPushButton::clicked,
            this,&PrintView::backRequested);

    connect(exitBtn, &QPushButton::clicked,
        this, &PrintView::exitRequested);

    connect(printBtnThermal, &QPushButton::clicked, this, [this]() {
        //emit startThermalPrintingRequested();
        emit startThermalPrintingRequested(m_sessionId);
    });


    connect(printBtnNetwork,
        &QPushButton::clicked,
        this,
        [this]()
        {
            emit startNetworkPrintingRequested(m_sessionId);
            //emit startNetworkPrintingRequested();
        });
    connect(postVitalsBtn,
            &QPushButton::clicked,
            this,
            [this]()
    {
        emit postVitalsRequested(m_sessionId);
    });

}
void PrintView::setData(const QVariantMap& d)
{
    qDebug() << "PRINT DATA MAP:" << d;

    auto getDouble = [&](const QString& key)
    {
        return d.contains(key) && !d[key].isNull()
               ? d[key].toDouble()
               : 0.0;
    };

    auto getInt = [&](const QString& key)
    {
        return d.contains(key) && !d[key].isNull()
               ? d[key].toInt()
               : 0;
    };

    auto getStr = [&](const QString& key)
    {
        return d.contains(key) && !d[key].isNull()
               ? d[key].toString()
               : QString();
    };

    //------------------------------------------------------
    // Patient
    //------------------------------------------------------

    QString name   = getStr("name");
    QString mobile = getStr("mobile");
    QString gender = getStr("gender");

    int age = getInt("age");

    m_sessionId = getInt("sessionId");
    m_patientId = getInt("patientId");

    qDebug() << "PrintView loaded session:" << m_sessionId;

    patientInfoLabel->setText(
        QString("Name : %1    Age : %2    Mobile : %3    Gender : %4")
            .arg(name.isEmpty() ? "--" : name)
            .arg(age > 0 ? QString::number(age) : "--")
            .arg(mobile.isEmpty() ? "--" : mobile)
            .arg(gender.isEmpty() ? "--" : gender));

    patientInfoLabel->setAlignment(
        Qt::AlignCenter | Qt::AlignVCenter);

    //------------------------------------------------------
    // Vitals
    //------------------------------------------------------

    double temperature = getDouble("temperature");
    double weight      = getDouble("weight");

    int height     = getInt("height");
    int spo2       = getInt("spo2");
    int pulse      = getInt("pulse");
    int systolic   = getInt("systolic");
    int diastolic  = getInt("diastolic");

    QString farVision  = getStr("farVision");
    QString nearVision = getStr("nearVision");

    tempLabel->setText(
        temperature > 0
        ? QString("%1 °F").arg(temperature,0,'f',1)
        : "--");

    spo2Label->setText(
        (spo2 > 0 && pulse > 0)
        ? QString("%1 % / %2 bpm")
            .arg(spo2)
            .arg(pulse)
        : "--");

    nibpLabel->setText(
        (systolic > 0 && diastolic > 0)
        ? QString("%1 / %2 mmHg")
            .arg(systolic)
            .arg(diastolic)
        : "--");

    weightLabel->setText(
        weight > 0
        ? QString("%1 kg")
            .arg(weight,0,'f',1)
        : "--");

    heightLabel->setText(
        height > 0
        ? QString("%1 cm")
            .arg(height)
        : "--");

    farVisionLabel->setText(
        farVision.isEmpty()
        ? "--"
        : farVision);

    nearVisionLabel->setText(
        nearVision.isEmpty()
        ? "--"
        : nearVision);

    //------------------------------------------------------
    // Derived Metrics
    //------------------------------------------------------

    double bmi =
        HealthMetricsService::calculateBMI(
            weight,
            height);

    QString bmiAnalysis =
        HealthMetricsService::calculateBMIAnalysis(
            bmi);

    double bmr =
        HealthMetricsService::calculateBMR(
            weight,
            height,
            age,
            gender);

    double bsa =
        HealthMetricsService::calculateBSA(
            weight,
            height);

    bmiLabel->setText(
        bmi > 0
        ? QString::number(bmi,'f',1)
        : "--");

    bmiAnalysisLabel->setText(
        bmiAnalysis);

    bmrLabel->setText(
        bmr > 0
        ? QString::number(bmr,'f',0) + " kcal/day"
        : "--");

    bsaLabel->setText(
        bsa > 0
        ? QString::number(bsa,'f',2) + " m²"
        : "--");
}
/* ================= SAFE DATA BINDING ================= */
/*working old implementation */
/*
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

    // -------- Patient Info --------

    
    //int sessionId = getInt("sessionId");
    //int patientId = getInt("patientId");
    QString name   = getStr("name");
    QString mobile = getStr("mobile");
    QString gender = getStr("gender");
    int age        = getInt("age");

    m_sessionId = getInt("sessionId");
    m_patientId = getInt("patientId");

    qDebug()
        << "PrintView loaded session:"
        << m_sessionId;
    
    patientInfoLabel->setText(
        QString("Name: %1\tAge: %2\tMobile: %3\tGender: %4")
            .arg(name)
            .arg(age > 0 ? QString::number(age) : "--")
            .arg(mobile)
            .arg(gender)
    );
    patientInfoLabel->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    
    // -------- Vitals -------- 

    double temp = getDouble("temperature");
    int spo2    = getInt("spo2");
    int pulse   = getInt("pulse");
    int systolic     = getInt("systolic");
    int diastolic     = getInt("diastolic");
    double weight = getDouble("weight");
    int height = getInt("height");
    QString farVision = getStr("farVision");
    QString nearVision = getStr("nearVision");

    tempLabel->setText(temp > 0 ? QString::number(temp) + " F" : "-- F");
    //tempLabel->setText(QString::number(temp) + " F" );
    spo2Label->setText(
        (spo2 > 0 && pulse > 0)
        ? QString("%1 / %2").arg(spo2).arg(pulse)
        : "--"
    );

    nibpLabel->setText(
        (systolic > 0 && diastolic > 0)
        ? QString("%1 / %2").arg(systolic).arg(diastolic)
        : "--"
    );

    weightLabel->setText(weight > 0 ? QString::number(weight) + " kg" : "-- kg");
    heightLabel->setText(height > 0 ? QString::number(height) + " cm" : "-- cm");

        farVisionLabel->setText(!farVision.isEmpty() ? farVision : "--");
        nearVisionLabel->setText(!nearVision.isEmpty() ? nearVision : "--");

    // -------- BMI -------- 

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
*/
void PrintView::setSessionId(int id)
{
    m_sessionId = id;
}

int PrintView::sessionId() const
{
    return m_sessionId;
}

int PrintView::patientId() const
{
    return m_patientId;
}

