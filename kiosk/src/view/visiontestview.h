#pragma once
#include <QWidget>

class QLabel;
class QPushButton;

class VisionTestView : public QWidget
{
    Q_OBJECT
public:
    explicit VisionTestView(QWidget* parent = nullptr);

    void setTestText(const QString& text);

signals:
    void startRequested();
    void okPressed();
    void cantSeePressed();
    void backPressed();

private:
    QLabel* testLabel;
};

