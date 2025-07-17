#ifndef LOGVIEWER_H
#define LOGVIEWER_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class LogViewer; }
QT_END_NAMESPACE

class LogViewer : public QDialog {
    Q_OBJECT

public:
    explicit LogViewer(QWidget *parent = nullptr);
    ~LogViewer();

    void loadLog(const QString &dbPath);

private:
    Ui::LogViewer *ui;
};

#endif // LOGVIEWER_H

