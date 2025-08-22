#include "MainWindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>

// -------- InputWorker Implementation --------
InputWorker::InputWorker(const QString &dev, QObject *parent)
    : QThread(parent), devicePath(dev) {}

void InputWorker::run() {
    int fd = open(devicePath.toStdString().c_str(), O_RDONLY);
    if (fd < 0) {
        qWarning() << "Failed to open" << devicePath;
        return;
    }

    struct input_event ev;
    while (read(fd, &ev, sizeof(ev)) > 0) {
        if (ev.type == EV_REL && ev.code == REL_X) {
            emit rotaryTurned(ev.value); // -1 or +1
        } else if (ev.type == EV_KEY && ev.code == KEY_ENTER) {
            emit buttonPressed(ev.value); // 1 press, 0 release
        }
    }
    close(fd);
}

// -------- MainWindow Implementation --------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), rotaryLabel(new QLabel("Rotary: 0")), buttonLabel(new QLabel("Button: Released"))
{
    auto *widget = new QWidget;
    auto *layout = new QVBoxLayout(widget);
    layout->addWidget(rotaryLabel);
    layout->addWidget(buttonLabel);
    setCentralWidget(widget);

    //worker = new InputWorker("/dev/input/event8", this); // rotary device
    /*Instead of relying on /dev/input/eventX, use persistent names: ls -l /dev/input/by-path/ You’ll see stable symlinks like:
	platform-rotary@0-event -> ../event8
	platform-rotary-sw-event -> ../event3*/
    worker = new InputWorker("/dev/input/by-path/platform-rotary@0-event", this);
    connect(worker, &InputWorker::rotaryTurned, this, &MainWindow::onRotaryTurned);

    //InputWorker *btnWorker = new InputWorker("/dev/input/event3", this); // switch device
    InputWorker *btnWorker = new InputWorker("/dev/input/by-path/platform-rotary-sw-event", this);
    connect(btnWorker, &InputWorker::buttonPressed, this, &MainWindow::onButtonPressed);

    worker->start();
    btnWorker->start();
}

MainWindow::~MainWindow() {}

void MainWindow::onRotaryTurned(int delta) {
    static int pos = 0;
    pos += delta;
    rotaryLabel->setText(QString("Rotary: %1").arg(pos));
}

void MainWindow::onButtonPressed(bool pressed) {
    buttonLabel->setText(pressed ? "Button: Pressed" : "Button: Released");
}

