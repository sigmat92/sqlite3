#include "recordsview.h"
#include "storage/record.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QDebug>

RecordsView::RecordsView(QWidget *parent)
    : BaseView("", parent)
{
    QVBoxLayout *layout = new QVBoxLayout(m_contentWidget);
    layout->setObjectName("contentLayout");
    table = new QTableView;
    table->setObjectName("recordsTable");
    model = new QStandardItemModel(this);
    model->setObjectName("recordsModel");
    table->setModel(model);

    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    table->horizontalHeader()->setStretchLastSection(true);

    layout->addWidget(table);

    //-------- BUTTONS -------- 

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->setObjectName("btnLayout");
    selectBtn = new QPushButton("Select");
    selectBtn->setObjectName("selectBtn");
    /*
        selectBtn->setStyleSheet(
        "font-size:28px;"
        "border-radius: 8px;"
        "font-weight:bold;"
        "background:#0d47a1;"
        "color:white;"
    );
    */
    exitBtn   = new QPushButton("Exit");
    exitBtn->setObjectName("exitBtn");
    /*
    exitBtn->setStyleSheet(
        "font-size:28px;"
        "border-radius: 8px;"
        "font-weight:bold;"
        "background:#455a64;"
        "color:white;"
    );
    */
    btnLayout->addWidget(selectBtn);
    //btnLayout->addWidget(exitBtn);

    layout->addLayout(btnLayout);

    connect(selectBtn, &QPushButton::clicked, this, [this]() {

        int id = getSelectedSessionId();

        if(id < 0)
        {
            QMessageBox::warning(this,"Warning","Select a record");
            return;
        }

        emit recordSelected(id);
    });

    connect(exitBtn, &QPushButton::clicked,
            this, &RecordsView::backRequested);
}

/* -------- SET DATA -------- */

void RecordsView::setData(const std::vector<Record>& records)
{
    model->clear();

    model->setHorizontalHeaderLabels(
        //{"Session ID", "Patient ID", "Date", "Time", "Name"}
        {"Patient ID", "Name","age","gender","mobile","temp","spo2",
          "pulse","sys/dia","weight","height", "Far Vision","Near Vision","Date","Time", }
    );

    for(const auto& r : records)
    {
        QList<QStandardItem*> row;

        //row << new QStandardItem(QString::number(r.sessionId));
        row << new QStandardItem(QString::number(r.patientId));
        row << new QStandardItem(r.name);
        row << new QStandardItem(QString::number(r.age));
        row << new QStandardItem(r.gender);
        row << new QStandardItem(QString::number(r.mobile));

        
        // -------- VITALS --------

        row << new QStandardItem(QString::number(r.temperature, 'f', 1)); // 1 decimal place
        row << new QStandardItem(QString::number(r.spo2));
        row << new QStandardItem(QString::number(r.pulse));
        row << new QStandardItem(QString::number(r.sys) + "/" + QString::number(r.dia)); // BP format
        row << new QStandardItem(QString::number(r.weight, 'f', 2)); // 2 decimal places
        row << new QStandardItem(QString::number(r.height));
        row << new QStandardItem(r.nearVision);
        row << new QStandardItem(r.farVision);

        row << new QStandardItem(r.date);
        row << new QStandardItem(r.time);

        model->appendRow(row);
    }
}

/* -------- GET SELECTED -------- */

int RecordsView::getSelectedSessionId()
{
    QModelIndex index = table->currentIndex();

    if(!index.isValid())
        return -1;

    int row = index.row();

    return model->item(row, 0)->text().toInt();
}