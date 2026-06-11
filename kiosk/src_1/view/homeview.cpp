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
    actionLayout->setObjectName("actionLayout");
    QPushButton *newTestBtn = new QPushButton("New Test");
    newTestBtn->setObjectName("newTestBtn");
    QPushButton *settingsBtn = new QPushButton("Settings");
    settingsBtn->setObjectName("settingsBtn");

    actionLayout->addWidget(newTestBtn);
    actionLayout->addWidget(settingsBtn);

    connect(newTestBtn,&QPushButton::clicked,this,[this](){

    clearPatientFields();
    unlockPatientFields();
    currentSessionId = -1; 
    emit resetSessionRequested();

    statusLabel->setText("Test Status: New test started");
});
    connect(settingsBtn,&QPushButton::clicked,this,[this](){
        qDebug() << "Settings button clicked in home view";
        emit settingsRequested();

    });

    layout->addWidget(actionBar);

    /* ---------------- STATUS ---------------- */

    statusLabel = new QLabel("Test Status: Ready...");
    statusLabel->setObjectName("statusLabel");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setMinimumHeight(45);

    layout->addWidget(statusLabel);

    /* ---------------- PATIENT PANEL ---------------- */

    QWidget *patientPanel = new QWidget;
    patientPanel->setObjectName("patientPanel");

    QGridLayout *pLayout = new QGridLayout(patientPanel);
    nameEdit = new QLineEdit;
    nameEdit->setObjectName("nameEdit");
    ageEdit = new QLineEdit;
    ageEdit->setObjectName("ageEdit");
    mobileEdit = new QLineEdit;
    mobileEdit->setObjectName("mobileEdit");

    maleBtn = new QRadioButton("Male");
    maleBtn->setObjectName("maleBtn");

    femaleBtn = new QRadioButton("Female");
    femaleBtn->setObjectName("femaleBtn");

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
    metricsPanel->setObjectName("metricsPanel");
    QGridLayout *grid = new QGridLayout(metricsPanel);

    struct MetricDef
    {
        QString title;
        QString status;
        std::function<void()> signal;
    };

    std::vector<MetricDef> metrics =
    {
        
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

        connect(card, &MetricCard::startRequested, this, [this, metrics, i]() {

            // ONLY emit measurement signal
            metrics[i].signal();

            statusLabel->setText("Test Status: " + metrics[i].status);

            qDebug() << metrics[i].title << "requested from home view";
        });

    }//for

    layout->addWidget(metricsPanel);

    /* ---------------- RESULTS PANEL ---------------- */
  
    QLabel *resultsTitle = new QLabel("Test Results :");
    resultsTitle->setAlignment(Qt::AlignCenter);

    QWidget *resultsPanel = new QWidget;

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

    connect(printBtn,&QPushButton::clicked,this,[this](){

    //if(currentSessionId <= 0)
    //{
    //    showError("No session available");
    //   return;
    //}

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
void HomeView::setSpO2Busy(bool busy)
{
    if(spo2Card)
        spo2Card->setBusy(busy);
}

void HomeView::setSpo2Text(const QString &text)
{
    qDebug() << "VIEW UPDATE:" << text;
    qDebug() << "spo2Card ptr:" << spo2Card;

    if(spo2Card)
        spo2Card->setValue(text);
}
/* ================= NIBP ================= */


void HomeView::setNIBPText(const QString &text)
{
    qDebug() << "HOME VIEW UPDATE final val :" << text;
    
     //qDebug() << "HOME VIEW UPDATE: NIBP Pressure:" << pressure;

    if(nibpCard)
    {
        nibpCard->setValue(text);
        nibpCard->update();
        nibpCard->repaint();
    }
}
//void HomeView::setNIBPText(const QString &text)
//{
//    qDebug() << "VIEW UPDATE:" << text;
//    qDebug() << "nibpCard ptr:" << nibpCard;
//    if(nibpCard)
//        nibpCard->setValue(text);
//}
void HomeView::setNIBPPressure(int pressure)
{
    qDebug() << "HOME VIEW UPDATE: NIBP Pressure:" << pressure;
    qDebug() << "nibpCard ptr:" << nibpCard;
    QString text = QString("%1")
                       .arg(pressure);

    if(nibpCard)
    {
        nibpCard->setValue(text);
        nibpCard->update();
        nibpCard->repaint();
    }

    //nibpCard->setValue(text);
    qDebug() << "NIBP Pressure updating on home view:" << text;
    //setNIBPText(text);
}
void HomeView::setNIBPBusy(bool busy)
{
    if(nibpCard)
        nibpCard->setBusy(busy);
}
/* ================= HEIGHT ================= */
void HomeView::setHeightText(const QString &text)
{
    qDebug() << "VIEW UPDATE:" << text;
    qDebug() << "heightCard ptr:" << heightCard;
    if(heightCard)
        heightCard->setValue(text);
}
void HomeView::setHeightBusy(bool busy)
{
    if(heightCard)
        heightCard->setBusy(busy);
}
/* ================= WEIGHT ================= */
void HomeView::setWeightText(const QString &text)
{
    qDebug() << "VIEW UPDATE:" << text;
    qDebug() << "weightCard ptr:" << weightCard;
    if(weightCard)
        weightCard->setValue(text);
}
void HomeView::setWeightBusy(bool busy)
{
    if(weightCard)
        weightCard->setBusy(busy);
}

void HomeView::onVitalsUpdated(int spo2,int pulse)
{
    qDebug() << "VIEW UPDATE:" << spo2 << pulse;
    //qDebug() << "temperatureCard ptr:" << spo2Card;
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

