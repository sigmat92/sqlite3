#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ConfigManager;

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

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    ConfigManager *config;
};

#endif // MAINWINDOW_H