#pragma once

#include "baseview.h"
#include <vector>

class QTableView;
class QPushButton;
class QStandardItemModel;
struct Record;

class RecordsView : public BaseView
{
    Q_OBJECT

public:
    explicit RecordsView(QWidget *parent = nullptr);

    void setData(const std::vector<Record>& records);

signals:
    void recordSelected(int sessionId);
    void backRequested();

private:
    QTableView *table;
    QStandardItemModel *model;

    QPushButton *selectBtn;
    QPushButton *exitBtn;

    int getSelectedSessionId();
};