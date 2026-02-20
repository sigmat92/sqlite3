#pragma once
#include <QWidget>

class QLabel;
class QPushButton;

class MetricCard : public QWidget
{
    Q_OBJECT
public:
    explicit MetricCard(const QString& title, QWidget* parent = nullptr);

    void setValue(const QString& value);
    void setBusy(bool busy);

signals:
    void startRequested();

private:
    QLabel* valueLabel;
    QPushButton* startBtn;
};

