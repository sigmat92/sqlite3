#pragma once
#include <QObject>
#include <QStringList>

class VisionTestView;

class VisionTestController : public QObject
{
    Q_OBJECT
public:
    explicit VisionTestController(VisionTestView* view,
                                  QObject* parent = nullptr);

private slots:
    void onStart();
    void onOk();
    void onCantSee();
    void onBack();

private:
    VisionTestView* view;
    QStringList testSequence { "CS", "DN", "RP", "ET", "ZO" };
    int index{0};
};

