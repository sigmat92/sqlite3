Project Overview
This Qt6 GUI app lets users:
•	Select and open a serial port (via QSerialPort)
•	Send and receive text data
•	View TX/RX data live in a text area
•	Save/load config to JSON (port, baud, interval, auto-send)
________________________________________
File Structure

cutecom-serial/
├── CMakeLists.txt
├── compile.sh
├── main.cpp
├── MainWindow.h / .cpp / .ui
├── ConfigManager.h / .cpp
________________________________________
main.cpp
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
•	Standard Qt app entry point.
•	Loads MainWindow (UI + logic).
________________________________________
MainWindow.ui (Qt Designer Preferred)
Includes widgets:
Widget Name	Type	Purpose
portComboBox	   QComboBox	       Serial port selection
baudRateBox	   QComboBox	       Baud rate selection
connectButton	   QPushButton	       Open/Close port
sendEdit	QLineEdit	User text input
sendButton	QPushButton	Send serial data
terminalText	QTextEdit	RX/TX log
autoSendCheck	QCheckBox	Optional for auto-send later
intervalSpin	QSpinBox	Optional interval setting
statusbar	QStatusBar	App messages
loadConfigButton	QPushButton	Load settings from JSON
saveConfigButton	QPushButton	Save settings to JSON
________________________________________
MainWindow.cpp — Serial Logic
Setup (constructor)
serial = new QSerialPort(this);
ui->setupUi(this);
•	Initializes UI and serial object.
for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
    ui->portComboBox->addItem(info.portName());
•	Lists all available serial ports in the dropdown.
ui->baudRateBox->addItems({"9600", "19200", "38400", "57600", "115200"});
•	Adds common baud rates.
Signals and Slots
connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::openOrCloseSerial);
connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendData);
connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
connect(ui->loadConfigButton, &QPushButton::clicked, this, &MainWindow::loadConfig);
connect(ui->saveConfigButton, &QPushButton::clicked, this, &MainWindow::saveConfig);
________________________________________
openOrCloseSerial()
Opens or closes the serial port:


serial->setPortName(ui->portComboBox->currentText());
serial->setBaudRate(ui->baudRateBox->currentText().toInt());
serial->open(QIODevice::ReadWrite);
Updates button text and shows message in status bar.
________________________________________
sendData()

QByteArray data = ui->sendEdit->text().toUtf8();
serial->write(data);
ui->terminalText->append("[TX] " + data);
Sends user-entered data and logs it in the terminal.
________________________________________
readData()

QByteArray data = serial->readAll();
ui->terminalText->append("[RX] " + QString::fromUtf8(data));
Receives data from serial port and appends it.
________________________________________
ConfigManager — Save/Load Settings
save()
QJsonObject obj;
obj["port"] = ui->portComboBox->currentText();
obj["baud"] = ui->baudRateBox->currentText();
Creates a JSON object from UI fields, then writes to file.
________________________________________
load()
ui->portComboBox->setCurrentText(obj["port"].toString());
ui->baudRateBox->setCurrentText(obj["baud"].toString());
Reads from JSON and restores UI values.
________________________________________
CMakeLists.txt
Uses Qt6 with auto tools:
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
Includes SerialPort module:
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets SerialPort)
________________________________________
compile.sh
Simple build script:

cmake .. -DCMAKE_PREFIX_PATH="/opt/Qt/6.5.3/gcc_64/lib/cmake"
cmake --build .
./cutecom-serial
________________________________________

