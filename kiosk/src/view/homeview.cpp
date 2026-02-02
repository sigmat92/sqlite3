#include "homeview.h"
//#include <QtWidgets>
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

/* =====================================================
 * Helper functions to cretate metric cards
 * ===================================================== */

 static QWidget* metricCard(const QString& title, QLabel*& valueLabel)
{
    QWidget* card = new QWidget;
    card->setStyleSheet("background:#e1f5fe; border-radius:8px;");

    auto* layout = new QVBoxLayout(card);
    layout->setContentsMargins(12, 12, 12, 12);

    QLabel* titleLabel = new QLabel(title);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-weight:bold;");

    valueLabel = new QLabel("--");
    valueLabel->setAlignment(Qt::AlignCenter);
    valueLabel->setStyleSheet("font-size:22px; font-weight:bold;");

    QPushButton* startBtn = new QPushButton("Start");
    startBtn->setMinimumHeight(36);
    startBtn->setStyleSheet("background:#0d47a1; color:white;");

    layout->addWidget(titleLabel);
    layout->addStretch();
    layout->addWidget(valueLabel);
    layout->addWidget(startBtn);

    return card;
}

/*
 static QWidget* metricCard(const QString& title)
{
    QWidget* card = new QWidget;
    card->setStyleSheet("background:#e1f5fe; border-radius:8px;");

    auto* layout = new QVBoxLayout(card);
    layout->setContentsMargins(12, 12, 12, 12);

    QLabel* label = new QLabel(title);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-weight:bold;");

    QPushButton* startBtn = new QPushButton("Start");
    startBtn->setMinimumHeight(40);
    startBtn->setStyleSheet("background:#0d47a1; color:white;");

    layout->addWidget(label);
    layout->addStretch();
    layout->addWidget(startBtn);

    return card;
}
*/
/*================vision test card============*/
static QWidget* visionTestCard(const QString& title)
{
    QWidget* card = new QWidget;
    card->setStyleSheet("background:#e1f5fe; border-radius:8px;");

    auto* layout = new QVBoxLayout(card);
    layout->setContentsMargins(12, 12, 12, 12);

    QLabel* label = new QLabel(title);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-weight:bold;");

    //QPushButton* startBtn = new QPushButton("Start");
    auto* vision = new QPushButton("👁 Vision Test");
    vision->setMinimumHeight(40);
    vision->setStyleSheet("background:#0d47a1; color:white;");

    layout->addWidget(label);
    layout->addStretch();
    layout->addWidget(vision);

    return card;
}

/*
QLineEdit* nameEdit;
QLineEdit* mobileEdit;
QLineEdit* ageEdit;
QRadioButton* maleBtn;
QRadioButton* femaleBtn;

void HomeView::clearPatient()
{
    nameEdit->clear();
    mobileEdit->clear();
    ageEdit->clear();
    maleBtn->setChecked(false);
    femaleBtn->setChecked(false);
}

void HomeView::setPatientName(const QString& name)
{
    nameEdit->setText(name);
}

void HomeView::setMobile(const QString& mobile)
{
    mobileEdit->setText(mobile);
}

void HomeView::setAge(int age)
{
    ageEdit->setText(QString::number(age));
}

void HomeView::setGender(const QString& gender)
{
    maleBtn->setChecked(gender.compare("male", Qt::CaseInsensitive) == 0);
    femaleBtn->setChecked(gender.compare("female", Qt::CaseInsensitive) == 0);
}

*/
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
    /*Settings Button*/
    QPushButton *settings = new QPushButton("⚙ Settings");

    newTest->setStyleSheet("background:#0d47a1; color:white; padding:8px 14px;");
    settings->setStyleSheet("background:#0d47a1; color:white; padding:8px 14px;");
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
    
    /*
    auto* haltBtn = new QPushButton("⏻");
    haltBtn->setObjectName("haltBtn");
    
    haltBtn->setFixedSize(48, 48);
    */
    connect(powerBtn, &QPushButton::clicked, this, []() {
    // Immediate halt
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

    mLayout->addWidget(metricCard("SpO2 / Pulse", spo2Value), 0, 0);
    mLayout->addWidget(metricCard("NIBP", nibpValue),         0, 1);
    mLayout->addWidget(metricCard("Height", heightValue),     1, 0);
    mLayout->addWidget(metricCard("Weight", weightValue),     1, 1);
    mLayout->addWidget(metricCard("Temperature", tempValue),  1, 2);
    mLayout->addWidget(visionTestCard("Vision Test"),        0, 2);
/*
    mLayout->addWidget(metricCard("SpO2 / Pulse"), 0, 0);
    mLayout->addWidget(metricCard("NIBP"),         0, 1);
    mLayout->addWidget(visionTestCard("VisionTest"),   0, 2);
    mLayout->addWidget(metricCard("Height"),       1, 0);
    mLayout->addWidget(metricCard("Weight"),       1, 1);
    mLayout->addWidget(metricCard("Temperature"),  1, 2);
*/
    root->addWidget(metricsPanel);


    /* ================= Test Status Strip =============*/

    QLabel *status = new QLabel("Test Status:");
    status->setStyleSheet("background:#bbdefb; padding:8px; font-weight:bold;");
    //
    //QPushButton *printBtn = new QPushButton("🖨 PRINT RESULT");
    //printBtn->setStyleSheet("background:#0d47a1; color:white; padding:8px;");

    //rLayout->addWidget(printBtn, 0, 2, 2, 1);
    //

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
//shuold come from domain
void HomeView::setSpO2(int spo2, int pulse)
{
    if (!spo2Value) return;
    spo2Value->setText(QString("%1 / %2").arg(spo2).arg(pulse));
}

void HomeView::setNIBP(const QString& value)
{
    if (!nibpValue) return;
    nibpValue->setText(value);
}

void HomeView::setHeight(int cm)
{
    if (!heightValue) return;
    heightValue->setText(QString::number(cm));
}

void HomeView::setWeight(double kg)
{
    if (!weightValue) return;
    weightValue->setText(QString::number(kg, 'f', 1));
}

void HomeView::setTemperature(double f)
{
    if (!tempValue) return;
    tempValue->setText(QString::number(f, 'f', 1));
}
//
