#ifndef VISIONTESTVIEW_H
#define VISIONTESTVIEW_H

#include "baseview.h"

#include <QLabel>
#include <QPushButton>

class VisionTestView : public BaseView
{
    Q_OBJECT

public:

    explicit VisionTestView(QWidget *parent = nullptr);

    /*
     * Returns selected mode
     */
    bool isNearMode() const;

public slots:

    /*
     * Called by VisionService
     */
    void displayLevel(
            QString letters,
            int fontSize);

    /*
     * Final result
     */
    void showResult(QString result);

signals:

    /*
     * START button
     */
    void startRequested();

    /*
     * PASS / FAIL
     */
    void answerSelected(QString answer);

    /*
     * Mode buttons
     */
    void nearModeSelected();

    void farModeSelected();

    /*
     * Exit
     */
    void exitRequested();

private slots:

    void onNearClicked();

    void onFarClicked();

private:

    void updateModeButtons();

private:

    QLabel *symbolLabel = nullptr;

    QLabel *resultLabel = nullptr;

    QLabel *adviceLabel = nullptr;

    QPushButton *nearButton = nullptr;

    QPushButton *farButton = nullptr;

    QPushButton *startButton = nullptr;

    QPushButton *okButton = nullptr;

    QPushButton *cantSeeButton = nullptr;

    bool m_nearMode = true;
};

#endif