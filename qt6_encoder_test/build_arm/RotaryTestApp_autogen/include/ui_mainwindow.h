/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelCount;
    QLabel *labelSwitch;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(400, 200);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        labelCount = new QLabel(centralwidget);
        labelCount->setObjectName("labelCount");
        labelCount->setAlignment(Qt::AlignCenter);
        labelCount->setStyleSheet(QString::fromUtf8("font-size: 36px;"));

        verticalLayout->addWidget(labelCount);

        labelSwitch = new QLabel(centralwidget);
        labelSwitch->setObjectName("labelSwitch");
        labelSwitch->setAlignment(Qt::AlignCenter);
        labelSwitch->setStyleSheet(QString::fromUtf8("font-size: 24px; color: blue;"));

        verticalLayout->addWidget(labelSwitch);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Rotary Test", nullptr));
        labelCount->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        labelSwitch->setText(QCoreApplication::translate("MainWindow", "Released", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
