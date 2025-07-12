/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
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
    QComboBox *comboWaveType;
    WaveformWidget *waveWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *btnStart;
    QPushButton *btnStop;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        comboWaveType = new QComboBox(centralwidget);
        comboWaveType->addItem(QString());
        comboWaveType->addItem(QString());
        comboWaveType->addItem(QString());
        comboWaveType->addItem(QString());
        comboWaveType->setObjectName("comboWaveType");

        verticalLayout->addWidget(comboWaveType);

        waveWidget = new WaveformWidget(centralwidget);
        waveWidget->setObjectName("waveWidget");

        verticalLayout->addWidget(waveWidget);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        btnStart = new QPushButton(centralwidget);
        btnStart->setObjectName("btnStart");

        hboxLayout->addWidget(btnStart);

        btnStop = new QPushButton(centralwidget);
        btnStop->setObjectName("btnStop");

        hboxLayout->addWidget(btnStop);


        verticalLayout->addLayout(hboxLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        comboWaveType->setItemText(0, QCoreApplication::translate("MainWindow", "Sine", nullptr));
        comboWaveType->setItemText(1, QCoreApplication::translate("MainWindow", "Square", nullptr));
        comboWaveType->setItemText(2, QCoreApplication::translate("MainWindow", "Triangle", nullptr));
        comboWaveType->setItemText(3, QCoreApplication::translate("MainWindow", "Pulse", nullptr));

        btnStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        (void)MainWindow;
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
