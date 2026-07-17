#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class MetricCard : public QWidget
{
    Q_OBJECT

public:
    explicit MetricCard(const QString &title, QWidget *parent=nullptr);

    void setValue(const QString &value);
    void setBusy(bool busy);
    //Rotary navigation: Activate the card (simulate a button click)
    void activate();

signals:
    void startRequested();

private:
    QLabel *titleLabel;
    QLabel *valueLabel;
    QPushButton *startButton;
};
