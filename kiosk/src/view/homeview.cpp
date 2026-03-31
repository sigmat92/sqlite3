#include "homeview.h"
#include "metriccard.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QMessageBox>
#include <QDebug>

HomeView::HomeView(QWidget *parent)
    : BaseView("", parent)
{
    auto *layout = new QVBoxLayout(m_contentWidget);

    /* ---------------- ACTION BAR ---------------- */

    QWidget *actionBar = new QWidget;
    QHBoxLayout *actionLayout = new QHBoxLayout(actionBar);

    QPushButton *newTestBtn = new QPushButton("New Test");
    QPushButton *settingsBtn = new QPushButton("Settings");

    newTestBtn->setStyleSheet(
        "font-size:28px;"
        "border-radius: 8px;"
        "font-weight:bold;"
        "background:#0d47a1;"
        "color:white;"
    );

    settingsBtn->setStyleSheet(
        "font-size:28px;"
        "border-radius: 8px;"
        "font-weight:bold;"
        "background:#455a64;"
        "color:white;"
    );

    actionLayout->addWidget(newTestBtn);
    actionLayout->addWidget(settingsBtn);

    connect(newTestBtn,&QPushButton::clicked,this,[this](){

        clearPatientFields();
        unlockPatientFields();
        emit resetSessionRequested();
        statusLabel->setText("Test Status: New test started");

    });

    connect(settingsBtn,&QPushButton::clicked,this,[this](){

        emit settingsRequested();

    });

    layout->addWidget(actionBar);

    /* ---------------- STATUS ---------------- */

    statusLabel = new QLabel("Test Status: Ready...");

    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setMinimumHeight(45);

    statusLabel->setStyleSheet(
        "background:#bbdefb;"
        "font-weight:bold;"
        "border-radius: 8px;"
        "font-size:22px;"
    );

    layout->addWidget(statusLabel);

    /* ---------------- PATIENT PANEL ---------------- */

    QWidget *patientPanel = new QWidget;
  
    patientPanel->setStyleSheet(
        "background:#bbdefb;"
        "font-weight:bold;"
        "font-size:20px;"
        "border-radius: 8px;"
    );

    QGridLayout *pLayout = new QGridLayout(patientPanel);
    nameEdit = new QLineEdit;
    nameEdit->setStyleSheet("QLineEdit { background-color: white; color: black; }");

    ageEdit = new QLineEdit;
    ageEdit->setStyleSheet("QLineEdit { background-color: white; color: black; }");
    mobileEdit = new QLineEdit;
    mobileEdit->setStyleSheet("QLineEdit { background-color: white; color: black; }");

    maleBtn = new QRadioButton("Male");
    maleBtn->setStyleSheet(" QRadioButton { background-color: white; color: black; }");
    femaleBtn = new QRadioButton("Female");
    femaleBtn->setStyleSheet(" QRadioButton { background-color: white; color: black; }");

    QWidget *genderBox = new QWidget;
    QHBoxLayout *gLayout = new QHBoxLayout(genderBox);
    gLayout->addWidget(maleBtn);
    gLayout->addWidget(femaleBtn);

    pLayout->addWidget(new QLabel("Patient Name"),0,0);
    pLayout->addWidget(new QLabel("Age"),0,1);

    pLayout->addWidget(nameEdit,1,0);
    pLayout->addWidget(ageEdit,1,1);

    pLayout->addWidget(new QLabel("Mobile Number"),2,0);
    pLayout->addWidget(new QLabel("Gender"),2,1);

    pLayout->addWidget(mobileEdit,3,0);
    pLayout->addWidget(genderBox,3,1);

    layout->addWidget(patientPanel);

    /* ---------------- METRIC GRID ---------------- */

    QWidget *metricsPanel = new QWidget;
    QGridLayout *grid = new QGridLayout(metricsPanel);

    struct MetricDef
    {
        QString title;
        QString status;
        std::function<void()> signal;
    };

    std::vector<MetricDef> metrics =
    {
        //title,status.signal
        {"Vision Test","Vision test started",[this]{ emit visionTestRequested(); }},
        {"SpO2 / Pulse","SpO2 measurement started",[this]{ emit startSpo2Requested(); }},
        {"NIBP","NIBP measurement started",[this]{ emit startNIBPRequested(); }},
        {"Height","Height measurement started",[this]{ emit startHeightRequested(); }},
        {"Weight","Weight measurement started",[this]{ emit startWeightRequested(); }},
        {"Temperature","Temperature measurement started",[this]{ emit startTemperatureRequested(); }}
    };

    const int columns = 3;

    for(size_t i=0;i<metrics.size();++i)
    {
        MetricCard *card = new MetricCard(metrics[i].title);

        // STORE POINTERS
        if(metrics[i].title == "Temperature")
            temperatureCard = card;

        if(metrics[i].title == "SpO2 / Pulse")
            spo2Card = card;

        if(metrics[i].title == "NIBP")
            nibpCard = card;

        if(metrics[i].title == "Weight")
            weightCard = card;

        if(metrics[i].title == "Height")
            heightCard = card;

        int row = i / columns;
        int col = i % columns;

        grid->addWidget(card,row,col);
        grid->setColumnStretch(0,1);
        grid->setColumnStretch(1,1);
        grid->setColumnStretch(2,1);

        connect(card,&MetricCard::startRequested,this,[this,card,metrics,i](){

    // 1. Create session FIRST (only for first measurement)
    if(metrics[i].title == "Temperature")
    {
        qDebug() << "EMITTING SESSION SIGNAL";

        emit startSessionRequested(
            patientName(),
            patientAge().toInt(),
            patientMobile(),
            patientGender()
        );
    
    }

    if(metrics[i].title == "SpO2 / Pulse")
    {
        qDebug() << "EMITTING SESSION SIGNAL";

        emit startSessionRequested(
            patientName(),
            patientAge().toInt(),
            patientMobile(),
            patientGender()
        );
            
    }
    
    if(metrics[i].title == "NIBP")
    {
        qDebug() << "EMITTING SESSION SIGNAL";

        emit startSessionRequested(
            patientName(),
            patientAge().toInt(),
            patientMobile(),
            patientGender()
        );
            
    }
    if(metrics[i].title == "Height")
    {
        qDebug() << "EMITTING SESSION SIGNAL";

        emit startSessionRequested(
            patientName(),
            patientAge().toInt(),
            patientMobile(),
            patientGender()
        );
            
    }
    if(metrics[i].title == "Weight")
    {
        qDebug() << "EMITTING SESSION SIGNAL";

        emit startSessionRequested(
            patientName(),
            patientAge().toInt(),
            patientMobile(),
            patientGender()
        );
            
    }
        if(metrics[i].title == "Visison Test")
    {
        qDebug() << "EMITTING SESSION SIGNAL";

        emit startSessionRequested(
            patientName(),
            patientAge().toInt(),
            patientMobile(),
            patientGender()
        );
            
    }

    // 2. THEN start measurement
    metrics[i].signal();

    statusLabel->setText("Test Status: " + metrics[i].status);

    qDebug() << metrics[i].title << "requested";
});

    }//for

    layout->addWidget(metricsPanel);

    /* ---------------- RESULTS PANEL ---------------- */
  
    QLabel *resultsTitle = new QLabel("Test Results :");
    resultsTitle->setAlignment(Qt::AlignCenter);

    resultsTitle->setStyleSheet(
        "background:#bbdefb;"
        "font-weight:bold;"
        "border-radius: 8px;"
        "font-size:24px;"
    );

    QWidget *resultsPanel = new QWidget;
    resultsPanel->setStyleSheet(
            "background:#bbdefb;"
            "font-weight:bold;"
            "font-size:22px;"
            "border-radius: 8px;"
        );
    QGridLayout *rLayout = new QGridLayout(resultsPanel);
    rLayout->setRowStretch(0,1);
    rLayout->setRowStretch(1,1);
    rLayout->setRowStretch(2,1);
    rLayout->setRowStretch(3,1);
    rLayout->addWidget(resultsTitle);

    QLabel *bodyMassIndexLabel = new QLabel("Body Mass Index");
    rLayout->addWidget(bodyMassIndexLabel,1,0);
    
    bmiLabel = new QLabel("--");
    rLayout->addWidget(bmiLabel,1,1);
    
    rLayout->addWidget(new QLabel("BMI Analysis"),1,2);
    bmiAnalysisLabel = new QLabel("--");
    rLayout->addWidget(bmiAnalysisLabel,1,3);
    rLayout->addWidget(new QLabel("Basal Metabolic Rate"),2,0);
    bmrLabel = new QLabel("--");
    rLayout->addWidget(bmrLabel,2,1);
   
    rLayout->addWidget(new QLabel("Body Surface Area"),2,2);
    bsaLabel = new QLabel("--");
    rLayout->addWidget(bsaLabel,2,3);
   
    rLayout->addWidget(new QLabel("Far Vision"),3,0);
    farVisionLabel = new QLabel("--");
    rLayout->addWidget(farVisionLabel,3,1);
  
    rLayout->addWidget(new QLabel("Near Vision"),3,2);
    nearVisionLabel = new QLabel("--");
    rLayout->addWidget(nearVisionLabel,3,3);
    rLayout->setRowStretch(3,1);
    layout->addWidget(resultsPanel);

    /* ---------------- PRINT BUTTON ---------------- */

    QPushButton *printBtn = new QPushButton("Print Results");

    printBtn->setStyleSheet(
        "font-size:28px;"
        "font-weight:bold;"
        "background:#0d47a1;"
        "color:white;"
        "border-radius: 5px;"
    );

    connect(printBtn,&QPushButton::clicked,this,[this](){

    if(currentSessionId <= 0)
    {
        showError("No session available");
        return;
    }

    emit startPrintingRequested(currentSessionId);
    statusLabel->setText("Test Status: Printing results...");
});

    layout->addWidget(printBtn);
}

/* ================= TEMPERATURE ================= */

void HomeView::setTemperatureBusy(bool busy)
{
    if(temperatureCard)
        temperatureCard->setBusy(busy);
}

void HomeView::setTemperatureText(const QString &text)
{
    qDebug() << "VIEW UPDATE:" << text;
    qDebug() << "temperatureCard ptr:" << temperatureCard;

    if(temperatureCard)
        temperatureCard->setValue(text);
}
/* ================= SPO2 ================= */

void HomeView::onVitalsUpdated(int spo2,int pulse)
{
    qDebug() << "VIEW UPDATE:" << spo2 << pulse;
    qDebug() << "temperatureCard ptr:" << spo2Card;
    if(spo2Card)
        spo2Card->setValue(QString("%1 / %2").arg(spo2).arg(pulse));

}

/* ================= PATIENT DATA ================= */

QString HomeView::patientName() const
{
    return nameEdit->text().trimmed();
}

QString HomeView::patientAge() const
{
    return ageEdit->text().trimmed();
}

QString HomeView::patientMobile() const
{
    return mobileEdit->text().trimmed();
}

QString HomeView::patientGender() const
{
    if(maleBtn->isChecked()) return "Male";
    if(femaleBtn->isChecked()) return "Female";
    return "";
}

/* ================= FIELD CONTROL ================= */

void HomeView::lockPatientFields()
{
    nameEdit->setReadOnly(true);
    ageEdit->setReadOnly(true);
    mobileEdit->setReadOnly(true);

    maleBtn->setEnabled(false);
    femaleBtn->setEnabled(false);
}

void HomeView::unlockPatientFields()
{
    nameEdit->setReadOnly(false);
    ageEdit->setReadOnly(false);
    mobileEdit->setReadOnly(false);

    maleBtn->setEnabled(true);
    femaleBtn->setEnabled(true);
}

void HomeView::clearPatientFields()
{
    nameEdit->clear();
    ageEdit->clear();
    mobileEdit->clear();

    maleBtn->setChecked(false);
    femaleBtn->setChecked(false);
}

/* ================= ERROR ================= */

void HomeView::showError(const QString &msg)
{
    QMessageBox::warning(this,"Error",msg);
}
void HomeView::setCurrentSessionId(int id)
{
    currentSessionId = id;
}
