1. Project Overview

A desktop Qt6.5.3 app that:

Connects to serial ports using QSerialPort

Sends/receives data

Displays terminal text (TX/RX)

Logs all transmissions into an SQLite database

Lets you view logs in a separate dialog

Supports config save/load as JSON

2. Component Breakdown

MainWindow — Main UI and serial logic
UI: port dropdown, baud rate, connect, send

Serial open/close

Data send/receive

Logs messages via Logger

Loads/saves config using ConfigManager

Launches LogViewer for browsing past logs

Logger — SQLite-based logger

Initializes DB (serial_log.db)

Creates logs table if not exists

Logs each TX/RX with timestamp

ConfigManager — Save/load UI settings

Stores selected port and baud rate in JSON

Reloads on next app open

LogViewer — Separate window to show logs

Loads SQLite DB with different connection name

Displays table using QSqlTableModel

3. Data Flow

Serial Send:

User types message -> Clicks Send

serial->write(...) sends it
->Terminal shows "TX: ...", and Logger logs it in DB
Serial Receive:

Serial port triggers readyRead()
->serial->readAll() reads data
->Terminal shows "RX: ...", and Logger logs it in DB
View Log:

User clicks "View Logs"
->Opens LogViewer
->Loads from SQLite into QTableView

 4. Signal/Slot Connections

In MainWindow.cpp constructor:

connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::openOrCloseSerial);
connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendData);
connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
These wire up user actions to functionality like opening the port, sending data, and reading it.

5. Database Structure

SQLite database: serial_log.db

CREATE TABLE logs (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  timestamp TEXT,
  direction TEXT, -- "TX" or "RX"
  message TEXT
);

6. GUI Components

MainWindow UI

QComboBox ->Serial port

QComboBox ->Baud rate

QLineEdit ->Send text

QPushButton ->Connect/Send/Save/Load/View Logs

QTextEdit ->Terminal output

LogViewer UI

QTableView ->Shows timestamped logs from SQLite

7. Config JSON Format

File: config.json

{
  "port": "ttyUSB0",
  "baudrate": "115200"
}

8. Build and Run

Run compile.sh:

./compile.sh

This:

Deletes and recreates build dir

Calls CMake with Qt6

Builds all sources

Runs the app

Summary of Features Implemented

Feature	Module

Serial TX/RX-->MainWindow
SQLite logging-->Logger
Log browser UI-->LogViewer
Config save/load-->ConfigManager

Qt6 UIs	.ui files

JSON + SQL support-->Qt built-in libs


