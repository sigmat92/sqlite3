#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Qt 6 Widgets Example");
    window.resize(300, 150);

    QVBoxLayout *layout = new QVBoxLayout(&window);

    QLabel *label = new QLabel("Welcome to Qt 6!", &window);
    QPushButton *button = new QPushButton("Click Me", &window);

    layout->addWidget(label);
    layout->addWidget(button);

    QObject::connect(button, &QPushButton::clicked, [&]() {
        label->setText("Button clicked!");
    });

    window.show();
    return app.exec();
}

