/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "waveformwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    WaveformWidget *waveWidget;
    QHBoxLayout *hboxLayout;
    QComboBox *comboWaveType;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QHBoxLayout *hboxLayout1;
    QLineEdit *editName;
    QPushButton *btnSave;
    QHBoxLayout *hboxLayout2;
    QComboBox *comboSaved;
    QPushButton *btnLoad;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1194, 488);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        waveWidget = new WaveformWidget(centralwidget);
        waveWidget->setObjectName("waveWidget");

        verticalLayout->addWidget(waveWidget);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        comboWaveType = new QComboBox(centralwidget);
        comboWaveType->setObjectName("comboWaveType");

        hboxLayout->addWidget(comboWaveType);

        btnStart = new QPushButton(centralwidget);
        btnStart->setObjectName("btnStart");

        hboxLayout->addWidget(btnStart);

        btnStop = new QPushButton(centralwidget);
        btnStop->setObjectName("btnStop");

        hboxLayout->addWidget(btnStop);


        verticalLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        editName = new QLineEdit(centralwidget);
        editName->setObjectName("editName");

        hboxLayout1->addWidget(editName);

        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName("btnSave");

        hboxLayout1->addWidget(btnSave);


        verticalLayout->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName("hboxLayout2");
        comboSaved = new QComboBox(centralwidget);
        comboSaved->setObjectName("comboSaved");

        hboxLayout2->addWidget(comboSaved);

        btnLoad = new QPushButton(centralwidget);
        btnLoad->setObjectName("btnLoad");

        hboxLayout2->addWidget(btnLoad);


        verticalLayout->addLayout(hboxLayout2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        btnStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        btnLoad->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        (void)MainWindow;
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
