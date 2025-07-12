Project Structure Overview

wavegen/
├── CMakeLists.txt              # Qt6 project config
├── main.cpp                    # Entry point
├── mainwindow.ui               # UI layout (via Qt Designer)
├── mainwindow.h / .cpp         # UI logic
├── waveformwidget.h / .cpp     # Custom waveform drawing widget
└── build_x86/                  # Build output

1. main.cpp: App Entry

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}

Starts the Qt event loop

Launches the MainWindow

2. mainwindow.ui: UI Design (Qt Designercan be used)

QComboBox → Selects waveform type

WaveformWidget (promoted widget) → Draws animated waveform

QPushButton "Start" / "Stop" → Control animation

Promotion of waveWidget to WaveformWidget is critical for custom drawing.

3. mainwindow.cpp: UI Controller

WaveformWidget* waveform = qobject_cast<WaveformWidget*>(ui->waveWidget);

connect(ui->btnStart, &QPushButton::clicked, this, [=]() {
    waveform->start();
});

connect(ui->btnStop, &QPushButton::clicked, this, [=]() {
    waveform->stop();
});

connect(ui->comboWaveType, &QComboBox::currentIndexChanged, this, [=](int index) {
    waveform->setWaveType(static_cast<WaveType>(index));
});

Responsibilities:

Listens for button & dropdown changes

Calls methods on WaveformWidget

4. WaveformWidget — The Drawing Engine

Key Members:

QTimer *timer;            // triggers periodic updates
WaveType currentWave;     // enum for selected waveform
int phase;                // horizontal animation shift

start() / stop()

void WaveformWidget::start() {
    running = true;
    timer->start(50);     // fires every 50ms
}

updateWave()

void WaveformWidget::updateWave() {
    phase += 5;           // move waveform left
    update();             // triggers repaint
}

paintEvent()

The logic of rendering:

void WaveformWidget::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.fillRect(rect(), Qt::white); // clear background

    // Skip drawing if stopped
    if (!running) return;

    // For each x-pixel, compute y based on wave formula
    for (int x = 0; x < width(); ++x) {
        float t = (x + phase) / (float)width();  // shift for animation
        float y = waveform function...

        float screenY = height()/2 - y * amplitude;
        points.append(QPointF(x, screenY));
    }

    p.drawPolyline(points);
}

Wave formulas:

WaveType	Formula used

SINE		y = sin(2πt)
SQUARE		y = sin(2πt) >= 0 ? 1 : -1
TRIANGLE	y = 2 * abs(2(t - floor(t + 0.5))) - 1
PULSE		y = (fmod(t, 0.25) < 0.1) ? 1 : -1

5. CMakeLists.txt: Qt6 Setup

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(WaveformGenerator
    main.cpp
    mainwindow.cpp
    waveformwidget.cpp
    mainwindow.ui
    mainwindow.h
    waveformwidget.h
)

target_link_libraries(WaveformGenerator PRIVATE Qt6::Widgets)
Sets up Qt6 Widgets support

Links required files

Includes the .ui and header sources

Summary: Data Flow

[User input]
  ↓
MainWindow connects → waveform->setWaveType / start / stop
                             ↓
                QTimer fires every 50ms
                             ↓
                 updateWave() → update()
                             ↓
                    paintEvent() draws new frame
Possible Expansions


Add amplitude/frequency sliders

Save waveform as image

Display waveform data as numbers (e.g., peak, RMS)

Export waveform as CSV

Cross-compile for i.MX93 with Qt6 + framebuffer


