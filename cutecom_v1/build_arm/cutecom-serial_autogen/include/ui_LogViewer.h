/********************************************************************************
** Form generated from reading UI file 'LogViewer.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGVIEWER_H
#define UI_LOGVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LogViewer
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;

    void setupUi(QDialog *LogViewer)
    {
        if (LogViewer->objectName().isEmpty())
            LogViewer->setObjectName("LogViewer");
        verticalLayout = new QVBoxLayout(LogViewer);
        verticalLayout->setObjectName("verticalLayout");
        tableView = new QTableView(LogViewer);
        tableView->setObjectName("tableView");

        verticalLayout->addWidget(tableView);


        retranslateUi(LogViewer);

        QMetaObject::connectSlotsByName(LogViewer);
    } // setupUi

    void retranslateUi(QDialog *LogViewer)
    {
        LogViewer->setWindowTitle(QCoreApplication::translate("LogViewer", "Log Viewer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogViewer: public Ui_LogViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGVIEWER_H
