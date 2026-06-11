#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>

class BaseView : public QWidget
{
    Q_OBJECT

public:
    explicit BaseView(const QString &title, QWidget *parent = nullptr);

protected:
    QWidget *m_contentWidget;
    QVBoxLayout *m_mainLayout;

    QLabel *m_dateTimeLabel;
    QLabel *m_statusIndicator;

    void startClock();

private:
    QWidget* createHeader(const QString &title);
    QWidget* createFooter();
};
