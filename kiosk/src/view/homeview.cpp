#include "homeview.h"
#include "metriccard.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTimer>
#include <QDateTime>
#include <QProcess>
#include <QDebug>
#include "controller/visiontestcontroller.h"
#include "view/visiontestview.h"
#include "view/settingsview.h"
#include "service/settingsservice.h"

HomeView::HomeView(QWidget* parent) : QWidget(parent)
{
//style
this->setStyleSheet(R"(
#headerBar {
    background-color: #000000;
}

#footerBar {
    background-color: #000000;
}

#headerTitle {
    color: white;
    font-size: 20px;
    font-weight: bold;
}

#headerTime {
    color: #DDDDDD;
    font-size: 20px;
    font-weight: bold;
}

#powerButton {
    background-color: transparent;
    color: red;
    font-size: 32px;
    border: none;
}

#footerText {
    color: #AAAAAA;
    font-size: 20px;
}
)");

    /* -------- SCREEN -------- */

    auto* root = new QVBoxLayout(this);
    root->setContentsMargins(12, 12, 12, 12);
    root->setSpacing(10);

   /* ================= Test Status Strip =============*/
    QLabel *status = new QLabel("Test Status:");
    status->setStyleSheet("background:#bbdefb; padding:8px; font-size:20px; font-weight:bold;");
    status->setMinimumHeight(60);
    status->setAlignment(Qt::AlignCenter);
    /* ================= HEADER ================= */
        
    auto* headerBar = new QWidget;
    headerBar->setObjectName("headerBar");
    headerBar->setFixedHeight(60);

    auto* headerLayout = new QHBoxLayout(headerBar);
    headerLayout->setContentsMargins(12, 6, 12, 6);

    /* METSL title */
    auto* title = new QLabel("metsl");
    title->setObjectName("headerTitle");
    /* New Test Button */
    QPushButton *newTest = new QPushButton("NEW TEST");

    connect(newTest, &QPushButton::clicked, this, [=]() {
        emit startNewTestRequested();
        qDebug() << "HomeView: New Test requested";
        status->setText("Test Status: New Test request starting...");
    });
    /*Settings Button*/
    QPushButton *settings = new QPushButton("⚙ Settings");
    newTest->setStyleSheet("background:#0d47a1; color:white; padding:8px 14px;");
    settings->setStyleSheet("background:#0d47a1; color:white; padding:8px 14px;");

    connect(settings, &QPushButton::clicked, this, [=]() {
    emit settingsRequested();   // cleaner name
    qDebug() << "HomeView: settings requested";
    status->setText("Test Status: Settings requested");
});



    //connect(settings, &QPushButton::clicked, this, [=]() {
    //    emit startSettingsRequested();
    //    qDebug() << "HomeView: settings start requested";
    //    status->setText("Test Status: Settings requested");

        //settingsView->show();
            //SettingsView* settingsView = new SettingsView;
    //settingsView->setModel(settingsService->getModel());
    //settingsView->show();
    //});
    

    /* RT Clock */
    m_timeLabel = new QLabel;
    m_timeLabel->setObjectName("headerTime");
    auto* clockTimer = new QTimer(this);

    connect(clockTimer, &QTimer::timeout, this, [this]() {
        m_timeLabel->setText(
        QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss")
       );
    });
    clockTimer->start(1000); // update every second

    /* Power button */
    
    auto* powerBtn = new QPushButton("⏻");
    powerBtn->setObjectName("powerButton");
    powerBtn->setFixedSize(48, 48);

    connect(powerBtn, &QPushButton::clicked, this, [=]() {
    status->setText("Test Status: Shutting Down...");
    QProcess::startDetached("poweroff");
    });

    /* Layout order */
    headerLayout->addWidget(title);
    headerLayout->addStretch();
    headerLayout->addWidget(newTest);
    headerLayout->addSpacing(8);
    headerLayout->addWidget(settings);
    headerLayout->addSpacing(16);
    headerLayout->addWidget(m_timeLabel);
    headerLayout->addSpacing(16);
    headerLayout->addWidget(powerBtn);

    root->addWidget(headerBar);

    /* ================= PATIENT INFO ================= */

    QWidget *patientPanel = new QWidget;
    //patientPanel->setStyleSheet("background:#b3e5fc;");
    patientPanel->setStyleSheet("background:#90caf9;");
    auto *pLayout = new QGridLayout(patientPanel);
    pLayout->setContentsMargins(16, 12, 16, 12);
    pLayout->setHorizontalSpacing(20);
    pLayout->setVerticalSpacing(10);

    //auto labelStyle = "font-weight:bold;"; //Common style foel labels

    pLayout->addWidget(new QLabel("Patient Name"), 0, 0);
    pLayout->addWidget(new QLabel("Patient Age"), 0, 1);

    //QLineEdit *nameEdit = new QLineEdit;
    //QLineEdit *ageEdit = new QLineEdit;
    nameEdit = new QLineEdit;
    ageEdit = new QLineEdit;
    mobileEdit = new QLineEdit;

    maleBtn = new QRadioButton("Male");
    femaleBtn = new QRadioButton("Female");

    
    //nameEdit->setReadOnly(true);
    //ageEdit->setReadOnly(true);

    pLayout->addWidget(nameEdit, 1, 0);
    pLayout->addWidget(ageEdit, 1, 1);

    pLayout->addWidget(new QLabel("Mobile Number"), 2, 0);
    pLayout->addWidget(new QLabel("Patient Gender"), 2, 1);

    //QLineEdit *mobileEdit = new QLineEdit;
    //mobileEdit->setReadOnly(true);

    QWidget *genderBox = new QWidget;
    auto *gLayout = new QHBoxLayout(genderBox);
    gLayout->addWidget(maleBtn);
    gLayout->addWidget(femaleBtn);

    pLayout->addWidget(mobileEdit, 3, 0);
    pLayout->addWidget(genderBox, 3, 1);

    root->addWidget(patientPanel);

    /* ================= VITALS ================= */
   

    /* ========= Health Metrics.Vision Test ============ */

    // ---- Health Metrics Panel ----

    QWidget* metricsPanel = new QWidget(this);
    metricsPanel->setObjectName("panel");

    auto* mLayout = new QGridLayout(metricsPanel);
    mLayout->setContentsMargins(16, 12, 16, 12);
    mLayout->setSpacing(12);

    // Create cards (store as members)
    visionTestCard  = new MetricCard("👁 Vision Test");
	spo2Card        = new MetricCard("SpO2 / Pulse");
	nibpCard        = new MetricCard("NIBP");
	heightCard      = new MetricCard("Height");
	weightCard      = new MetricCard("Weight");
	temperatureCard = new MetricCard("Temperature");
 
    // vision test start
    connect(visionTestCard, &MetricCard::startRequested,
            this, &HomeView::startVisionTestRequested);
    // Debug (optional – remove later)
    connect(this, &HomeView::startVisionTestRequested, this, [=]{
    qDebug() << "HomeView: Vision Test start requested";
    status->setText("Test Status: Vision Test starting...");
    auto* v = new VisionTestView;
    new VisionTestController(v, v);
    //v->showFullScreen();   // kiosk mode
    v->show();
    });
    
    //connect(view, &HomeView::visionTestRequested, this, [this]() {
    //auto* v = new VisionTestView;
    //new VisionTestController(v, v);
    //v->showFullScreen();   // kiosk mode
//});
    // Spo2 start
    connect(spo2Card, &MetricCard::startRequested,
            this, &HomeView::startSpo2Requested);
    // Debug (optional – remove later)
    connect(this, &HomeView::startSpo2Requested, this, [=]{
    qDebug() << "HomeView: SpO2 start requested";
    status->setText("Test Status: SpO2 measurement started...");
    });
    // NIBPstart
    connect(nibpCard, &MetricCard::startRequested,
            this, &HomeView::startNIBPRequested);
    // Debug (optional – remove later)
    connect(this, &HomeView::startNIBPRequested, this, [=]{
    qDebug() << "HomeView: NIBP start requested";
    status->setText("Test Status: NIBP measurement started...");
    });
    // Height start
    connect(heightCard, &MetricCard::startRequested,
            this, &HomeView::startHeightRequested);
    // Debug (optional – remove later)
    connect(this, &HomeView::startHeightRequested, this, [=]{
    qDebug() << "HomeView: Height start requested";
    status->setText("Test Status: Height measurement started...");
    });
    // Weight start
    connect(weightCard, &MetricCard::startRequested,
            this, &HomeView::startWeightRequested);
    // Debug (optional – remove later)
    connect(this, &HomeView::startWeightRequested, this, [=]{
    qDebug() << "HomeView: Weight start requested";
    status->setText("Test Status: Weight measurement started...");
    });

	// Temperature start ->emiting sigmnal controlller ->handles it
    connect(temperatureCard, &MetricCard::startRequested,
            this, &HomeView::startTemperatureRequested);

    connect(this, &HomeView::startTemperatureRequested, this, [=]{
    qDebug() << "HomeView: Temperature start requested";
    status->setText("Test Status: Temperature measurement started...");
    
     //status->setText("Test Status:");
    });

    mLayout->addWidget(spo2Card, 0, 0);
    mLayout->addWidget(nibpCard, 0, 1);
    mLayout->addWidget(heightCard,1, 0);
    mLayout->addWidget(weightCard,1, 1);
    
    mLayout->addWidget(temperatureCard,1, 2);
    
    mLayout->addWidget(visionTestCard,0, 2);

    root->addWidget(metricsPanel);
    
    //QPushButton *printBtn = new QPushButton("🖨 PRINT RESULT");
    //printBtn->setStyleSheet("background:#0d47a1; color:white; padding:8px;");

    //rLayout->addWidget(printBtn, 0, 2, 2, 1);
    root->addWidget(status);
    //root->addWidget(printBtn);
    /* ================= BMI + ACTIONS ================= */
    QWidget *results = new QWidget;
    results->setStyleSheet("background:#90caf9;");
    auto *rLayout = new QGridLayout(results);

    rLayout->addWidget(new QLabel("Test Results :"), 0, 0);
    rLayout->addWidget(new QLabel("Body Mass Index"), 1, 0);
    rLayout->addWidget(new QLabel(" -- "), 1, 1);
    rLayout->addWidget(new QLabel("BMI Analysis"), 1, 2);
    rLayout->addWidget(new QLabel(" -- "), 1, 3);
    rLayout->addWidget(new QLabel("Basal Metabolic Rate"), 2, 0);
    rLayout->addWidget(new QLabel(" -- "), 2, 1);
    rLayout->addWidget(new QLabel("Body Surface Area"), 2, 2);
    rLayout->addWidget(new QLabel(" -- "), 2, 3);
    rLayout->addWidget(new QLabel("Far Vision"), 3, 0);
    rLayout->addWidget(new QLabel(" -- "), 3, 1);
    rLayout->addWidget(new QLabel("Near Vision"), 3, 2);
    rLayout->addWidget(new QLabel(" -- "), 3, 3);

    //QPushButton *printBtn = new QPushButton("🖨 Print Results");
    //printBtn->setStyleSheet("background:#0d47a1; color:white; padding:8px 14px;");

    auto* printBtn = new QPushButton("🖨 Print Results");
    printBtn->setMinimumHeight(40);
    printBtn->setStyleSheet("background:#0d47a1; color:white;");
    connect(printBtn, &QPushButton::clicked, this, [=]() {
        emit startPrintingRequested();
        qDebug() << "HomeView: print button clicked";
        status->setText("Test Status: Printing results...");
    });
    //printBtn->setStyleSheet("background:#0d47a1; color:white; padding:8px;");

    //rLayout->addWidget(printBtn, 0, 2, 2, 1);

    root->addWidget(results);
    
    //root->addWidget(printBtn,0,Qt::AlignRight);
    /* ================= FOOTER ================= */

    auto* footerBar = new QWidget;
    footerBar->setObjectName("footerBar");
    footerBar->setFixedHeight(60);

    auto* footerLayout = new QHBoxLayout(footerBar);
    footerLayout->setContentsMargins(12, 4, 12, 4);

    auto* statusLabel = new QLabel("Care Nest Mini v1.0.0");
    statusLabel->setObjectName("footerText");

    auto* versionLabel = new QLabel("Care Nest Mini v1.0.0");
    versionLabel->setObjectName("footerText");

    footerLayout->addWidget(statusLabel);
    //footerLayout->addStretch();
    footerLayout->addWidget(printBtn,0,Qt::AlignRight);
    //footerLayout->addWidget(versionLabel,0,Qt::AlignLeft);

    root->addWidget(footerBar);
}

void HomeView::setTemperatureBusy(bool busy)
{
    if (temperatureCard)
        temperatureCard->setBusy(busy);
}

void HomeView::setTemperatureText(const QString& text)
{
    if (temperatureCard)
        temperatureCard->setValue(text);
}

//
void HomeView::onVitalsUpdated(int spo2, int pulse)
{
    if (spo2Card)
        spo2Card->setValue(QString("%1 / %2").arg(spo2).arg(pulse));
}