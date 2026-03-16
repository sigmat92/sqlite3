#pragma once
#include "baseview.h"
#include <QPushButton>
#include <QLabel>

class VisionTestView : public BaseView
{
    Q_OBJECT

public:
    explicit VisionTestView(QWidget *parent = nullptr);

    void setLeftResult(const QString &value);
    void setRightResult(const QString &value);

signals:
    void leftStartRequested();
    void rightStartRequested();
    void backRequested();
    void exitRequested();

private:
    void setupUi();

    QPushButton *m_leftBtn;
    QPushButton *m_rightBtn;
    QPushButton *m_backBtn;
    QPushButton *m_exitBtn;

    QLabel *m_leftResult;
    QLabel *m_rightResult;
    
};