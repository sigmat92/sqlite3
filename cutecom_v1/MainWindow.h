#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ConfigManager;
class Logger;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *getUi() const { return ui; }

private slots:
    void loadConfig();
    void saveConfig();
    void openOrCloseSerial();
    void sendData();
    void readData();
    void showLogViewer();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    ConfigManager *config;
    Logger *logger;
};

#endif // MAINWINDOW_H

