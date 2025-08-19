#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QThread>

class InputWorker : public QThread {
    Q_OBJECT
public:
    InputWorker(const QString &dev, QObject *parent = nullptr);
    void run() override;

signals:
    void rotaryTurned(int delta);
    void buttonPressed(bool pressed);

private:
    QString devicePath;
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRotaryTurned(int delta);
    void onButtonPressed(bool pressed);

private:
    QLabel *rotaryLabel;
    QLabel *buttonLabel;
    InputWorker *worker;
};

#endif // MAINWINDOW_H

