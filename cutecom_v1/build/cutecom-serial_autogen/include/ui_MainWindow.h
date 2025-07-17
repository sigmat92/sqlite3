/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *hboxLayout;
    QComboBox *portComboBox;
    QComboBox *baudRateBox;
    QCheckBox *autoSendCheck;
    QSpinBox *intervalSpin;
    QHBoxLayout *hboxLayout1;
    QPushButton *connectButton;
    QPushButton *loadConfigButton;
    QPushButton *saveConfigButton;
    QPushButton *viewLogButton;
    QTextEdit *terminalText;
    QHBoxLayout *hboxLayout2;
    QLineEdit *sendEdit;
    QPushButton *sendButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        portComboBox = new QComboBox(centralwidget);
        portComboBox->setObjectName("portComboBox");

        hboxLayout->addWidget(portComboBox);

        baudRateBox = new QComboBox(centralwidget);
        baudRateBox->setObjectName("baudRateBox");

        hboxLayout->addWidget(baudRateBox);

        autoSendCheck = new QCheckBox(centralwidget);
        autoSendCheck->setObjectName("autoSendCheck");

        hboxLayout->addWidget(autoSendCheck);

        intervalSpin = new QSpinBox(centralwidget);
        intervalSpin->setObjectName("intervalSpin");

        hboxLayout->addWidget(intervalSpin);


        mainLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        connectButton = new QPushButton(centralwidget);
        connectButton->setObjectName("connectButton");

        hboxLayout1->addWidget(connectButton);

        loadConfigButton = new QPushButton(centralwidget);
        loadConfigButton->setObjectName("loadConfigButton");

        hboxLayout1->addWidget(loadConfigButton);

        saveConfigButton = new QPushButton(centralwidget);
        saveConfigButton->setObjectName("saveConfigButton");

        hboxLayout1->addWidget(saveConfigButton);

        viewLogButton = new QPushButton(centralwidget);
        viewLogButton->setObjectName("viewLogButton");

        hboxLayout1->addWidget(viewLogButton);


        mainLayout->addLayout(hboxLayout1);

        terminalText = new QTextEdit(centralwidget);
        terminalText->setObjectName("terminalText");

        mainLayout->addWidget(terminalText);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName("hboxLayout2");
        sendEdit = new QLineEdit(centralwidget);
        sendEdit->setObjectName("sendEdit");

        hboxLayout2->addWidget(sendEdit);

        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName("sendButton");

        hboxLayout2->addWidget(sendButton);


        mainLayout->addLayout(hboxLayout2);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CuteCom Serial Clone", nullptr));
        autoSendCheck->setText(QCoreApplication::translate("MainWindow", "Auto Send", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        loadConfigButton->setText(QCoreApplication::translate("MainWindow", "Load Config", nullptr));
        saveConfigButton->setText(QCoreApplication::translate("MainWindow", "Save Config", nullptr));
        viewLogButton->setText(QCoreApplication::translate("MainWindow", "View Logs", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
