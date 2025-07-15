Project Structure

WaveformGenerator_Persistent/
├── main.cpp
├── mainwindow.h / mainwindow.cpp
├── waveformwidget.h / waveformwidget.cpp
├── waveformdb.h / waveformdb.cpp
├── mainwindow.ui
├── CMakeLists.txt
└── waveforms.db  <-- (created at runtime)
main.cpp

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
Launches the Qt application.

Displays MainWindow.

mainwindow.ui (UI Layout)

Contains:

WaveformWidget (custom QWidget)

QComboBox (waveform type)

QPushButton (Start / Stop)

QLineEdit (Name for saving)

QPushButton (Save)

QComboBox (Saved waveform list)

QPushButton (Load)

Defined as XML (mainwindow.ui) and auto-compiled with uic.

mainwindow.h / mainwindow.cpp

mainwindow.h

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void connectSignals();
    void refreshSavedList();
};

mainwindow.cpp

#include "waveformwidget.h"
#include "waveformdb.h"

MainWindow::MainWindow(...) {
    ...
    ui->comboWaveType->addItems({ "Sine", "Square", "Triangle", "Pulse" });
    connectSignals();
    refreshSavedList();
}

Signal Connections:

connect(ui->btnStart, &QPushButton::clicked, this, [&]() {
    ui->waveWidget->start();
});
connect(ui->btnStop, &QPushButton::clicked, this, [&]() {
    ui->waveWidget->stop();
});
connect(ui->comboWaveType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&](int index) {
    ui->waveWidget->setWaveType(static_cast<WaveType>(index));
});

Save/Load:

connect(ui->btnSave, &QPushButton::clicked, this, [&]() {
    QString name = ui->editName->text();
    if (!name.isEmpty()) {
        WaveformDB::instance().save(name, ui->waveWidget->getCurrentWaveform());
        refreshSavedList();
    }
});

connect(ui->btnLoad, &QPushButton::clicked, this, [&]() {
    QString name = ui->comboSaved->currentText();
    auto data = WaveformDB::instance().load(name);
    if (!data.isEmpty()) {
        ui->waveWidget->setCustomWaveform(data);
    }
});

 waveformwidget.h / waveformwidget.cpp
 
waveformwidget.h

enum class WaveType { Sine, Square, Triangle, Pulse };

class WaveformWidget : public QWidget {
    ...
    void start();
    void stop();
    void setWaveType(WaveType type);
    void setCustomWaveform(const QVector<double> &samples);
    QVector<double> getCurrentWaveform() const;
};
waveformwidget.cpp
generateWave() fills samples[] with waveform points.

updateWave() shifts waveform over time (for animation).

paintEvent() draws waveform using QPainter.

cpp
Copy
Edit
void WaveformWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    ...
    for (int i = 1; i < samples.size(); ++i) {
        int x1 = ..., y1 = ..., x2 = ..., y2 = ...;
        p.drawLine(x1, y1, x2, y2);
    }
}
waveformdb.h / waveformdb.cpp

Stores waveform samples in SQLite as JSON strings

waveformdb.h

class WaveformDB {
public:
    static WaveformDB& instance();
    void save(const QString& name, const QVector<double>& waveform);
    QVector<double> load(const QString& name);
    QStringList listWaveforms() const;
};

waveformdb.cpp

WaveformDB::WaveformDB() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("waveforms.db");
    db.open();
    ensureTable();
}

void WaveformDB::save(...) {
    QJsonArray arr;
    for (double d : waveform) arr.append(d);
    ...
    q.prepare("REPLACE INTO waveforms (name, data) VALUES (?, ?)");
    ...
}

QVector<double> WaveformDB::load(...) {
    ...
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    for (const auto& val : doc.array())
        result.append(val.toDouble());
    ...
}

SQL Table:

CREATE TABLE IF NOT EXISTS waveforms (
    name TEXT PRIMARY KEY,
    data TEXT
)

CMakeLists.txt

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

qt_add_executable(WaveformGenerator
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    waveformwidget.cpp waveformwidget.h
    waveformdb.cpp waveformdb.h
)

target_link_libraries(WaveformGenerator PRIVATE Qt6::Widgets Qt6::Sql)

How Save/Load Works

When you click Save:

Current waveform samples (QVector<double>) are serialized to JSON

JSON string is saved to SQLite

When you click Load:

JSON string is retrieved by name

Deserialized back to QVector<double>

Passed to WaveformWidget::setCustomWaveform()

Build & Run

mkdir build && cd build
cmake ..
make -j$(nproc)
./WaveformGenerator
