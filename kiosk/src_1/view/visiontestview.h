#pragma once
#include "baseview.h"

class QLabel;
class QPushButton;

class VisionTestView : public BaseView
{
    Q_OBJECT

public:
    explicit VisionTestView(QWidget* parent = nullptr);

signals:
    void startRequested();
    void answerSelected(QString answer);
    void exitRequested();

public slots:
    void displaySymbol(QString symbol);
    void showResult(QString result);
    
private:
    QLabel* statusLabel;
    QLabel* symbolLabel;
    QLabel* resultLabel;
};