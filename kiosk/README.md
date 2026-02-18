

Already have layers:

Model
View
Controller
Service
Platform
Storage (SQLite3)


Let's integrate the Vitals FSM + auto-detect cleanly into this structure.

Clean layer responsibility mapping

Where FSM belongs

Signal/data flow

Thread model

SQLite integration pattern

Minimal class skeletons (production-ready structure)

Where the FSM belongs

Your UART protocol logic is:

Hardware-specific

Serial-specific

Timing-sensitive

Not UI logic

It belongs in:

platform/
    UartDriver
    ProtocolParser
service/
    VitalsService (FSM)


NOT in controller.
NOT in view.
NOT in model.

Final Architecture (Clean)
View
  ↑
Controller
  ↑
Service (VitalsService)
  ↑
Platform (UartDriver + ProtocolParser)
  ↑
Hardware (/dev/ttyACM0)

Service → Storage (SQLite3)

Responsibilities per Layer

Platform Layer
UartDriver

Open/close UART

Send raw bytes

Read raw frames

ProtocolParser

Parse [CTRL][NOB][PAYLOAD]

Emit typed events:

TemperatureReceived

Spo2Received

WeightReceived

HeightReceived

NibpReceived

SensorAbsent

Platform should NOT:

Know about UI

Know about SQLite

Store data

Contain business logic

Service Layer (VitalsService)

Owns:

FSM state machine

Sensor auto-detection

Retry logic

Aggregation

Timeout policy

Produces:

VitalsData struct

SensorPresenceMask

“MeasurementComplete” event

Calls:

Storage to persist

Model Layer

Contains:

struct VitalsData {
    float temperature;
    int spo2;
    float weight;
    int height;
    int sys;
    int dia;
    int mean;
    uint32_t presenceMask;
};


No logic.
Just data.

Controller Layer

Receives UI actions

Calls VitalsService.startMeasurement()

Subscribes to service updates

Updates View

No UART here.

Storage Layer (SQLite3)

Responsible for:

CREATE TABLE vitals (
    id INTEGER PRIMARY KEY,
    timestamp INTEGER,
    temperature REAL,
    spo2 INTEGER,
    weight REAL,
    height INTEGER,
    sys INTEGER,
    dia INTEGER,
    mean INTEGER,
    presenceMask INTEGER
);


Only stores final results.

Event Flow (Runtime)

User presses “Start”:

View → Controller → VitalsService.start()
VitalsService → FSM starts
FSM → UartDriver send
Parser → emits events
VitalsService aggregates
VitalsService → emits vitalsReady()
Controller → updates View
VitalsService → Storage.save()

Thread Model (IMPORTANT)

UART MUST NOT block UI thread.

Recommended:

VitalsService runs in worker thread
UartDriver is blocking read
Parser runs in same worker thread


In Qt:

Use QThread

Or moveToThread()

In pure C++:

Use std::thread

Concrete Class Layout
platform/UartDriver.hpp
class UartDriver {
public:
    bool open(const std::string& dev);
    void close();
    void send(const std::vector<uint8_t>& data);
    bool readFrame(uint8_t& ctrl, std::vector<uint8_t>& payload);

private:
    int fd = -1;
};

platform/ProtocolParser.hpp
class ProtocolParser {
public:
    void process(uint8_t ctrl,
                 const std::vector<uint8_t>& payload,
                 std::function<void(const SensorEvent&)> cb);
};

service/VitalsService.hpp
class VitalsService {
public:
    void startMeasurement();
    void stop();

    std::function<void(const VitalsData&)> onVitalsReady;
    std::function<void(uint32_t)> onPresenceUpdate;

private:
    void fsmLoop();
};

Presence Mask (clean design)

Define:

enum SensorBit {
    SENSOR_TEMP   = 1 << 0,
    SENSOR_SPO2   = 1 << 1,
    SENSOR_WEIGHT = 1 << 2,
    SENSOR_HEIGHT = 1 << 3,
    SENSOR_NIBP   = 1 << 4
};


VitalsService sets bits when valid data arrives.

SQLite Integration (Service → Storage)

Inside VitalsService when FSM completes:

storage.saveVitals(vitalsData);


Storage layer:

void Storage::saveVitals(const VitalsData& v)
{
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db,
        "INSERT INTO vitals VALUES (NULL,?,?,?,?,?,?,?,?,?)",
        -1, &stmt, nullptr);

    sqlite3_bind_int64(stmt, 1, time(nullptr));
    sqlite3_bind_double(stmt, 2, v.temperature);
    sqlite3_bind_int(stmt, 3, v.spo2);
    ...
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}


Service never touches SQL directly.

What NOT to Do

Do not put UART in Controller
Do not write SQLite inside parser
Do not let View read serial
Do not mix FSM into UI

Recommended Production Structure
src/
  model/
  view/
  controller/
  service/
      VitalsService.cpp
  platform/
      UartDriver.cpp
      ProtocolParser.cpp
  storage/
      SqliteStorage.cpp

Professional Insight

system is now:

Deterministic

Layer-separated

Testable

Replaceable (mock UART)

Replaceable (mock SQLite)

Replaceable (future BLE instead of UART)

That is medical-device-grade architecture.



Print Service:

On boot:

System boots
↓
cupsd starts (userspace)
↓
print-helper starts
↓
Qt6 app starts
↓
Qt app talks to print-helper (TCP / UNIX socket)
↓
Printing works reliably


Scanner,UI etc → unchanged

1.High-level architecture :
Qt6App
  └── PrintServiceClient (Model)
        ↓ TCP / UNIX socket
Print Helper (C++)
  ├── Converts image/PDF
  ├── Calls CUPS API or lp
  └── Error handling
        ↓
CUPS daemon (cupsd)
  ├── USB backend
  ├── Pantum filter
  └── Printer

Why this is correct

Decoupled
Restartable
Debuggable
Upgradeable
Industry standard

2.Directory layout (clean + contained)

Install everything outside rootfs:

/opt/print/
├── sbin/cupsd
├── bin/
│   ├── lp
│   ├── lpstat
│   └── print-helper
├── lib/
│   └── libcups.so
├── libexec/cups/
│   ├── backend/usb
│   └── filter/pantum-filter
├── etc/cups/
│   ├── cupsd.conf
│   └── printers.conf
└── var/spool/cups


No conflict with system
No Yocto rebuild
Fully portable

Protocol Parser:

| Layer            | Status             |
| ---------------- | -------------------|
| UART             | stable             |
| Protocol parsing | correct            |
| Binary decoding  | exact Python match |
| Model            | correct            |
| Controller       | correct            |
| UI update        | correct            |
| User interaction | fixed              |

User clicks Start
→ Button disables
→ ProtocolController runs
→ First valid value arrives
→ UI updates value
→ Button re-enables


Build & install ZXing-cpp
cd ~
git clone https://github.com/zxing-cpp/zxing-cpp.git
cd zxing-cpp
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make -j$(nproc)
sudo make install
sudo ldconfig

This installs:

/usr/local/include/ZXing/
    BarcodeWriter.h
    ReadBarcode.h
    ImageView.h
/usr/local/lib/libZXing.so
/usr/local/lib/cmake/ZXing/ZXingConfig.cmake



STEP 0 — What we are building (mental model)

┌──────────────────────────────┐
│          UI / Views          │  Qt Widgets (.ui / QWidget)
├──────────────────────────────┤
│        Controllers           │  Glue: UI ↔ Services
├──────────────────────────────┤
│        Application Services  │  State, workflows, sessions
├──────────────────────────────┤
│        Domain / Model        │  Patient, Vitals, Records
├──────────────────────────────┤
│        Infrastructure        │  Hardware, DB, OS
└──────────────────────────────┘

1.

UartDevice        (bytes)
   ↓
UartParser        (protocol)
   ↓
SessionService    (workflow/state)
   ↓
HomeController    (routing)
   ↓
HomeView          (display)

2.

[ UI Start Button ]
        ↓
HomeView::startTemperatureRequested()
        ↓
HomeController
        ↓
ProtocolController::requestTemperature()
        ↓
UartDevice::send()
        ↓
ProtocolParser::temperature
        ↓
VitalsModel::setTemperature()
        ↓
VitalsModel::temperatureChanged()
        ↓
HomeController::onTemperatureChanged()
        ↓
HomeView::setTemperature()

3.

USB Camera (GRAY8)
   │
   ▼
V4L2 mmap (platform)
   │
   ▼
CameraController (thread)
   │ emits QImage(Grayscale8)
   ├────────────► CameraViewWidget (preview)
   │
   └────────────► BarcodeScanner (ZXing)
                       │
                       ▼
                  BarcodeModel
                       │
                       ▼
                 SQLiteRecorder


ZXing loves grayscale — this is the fastest and cleanest path.

STEP 1 — Project skeleton (from scratch)

kiosk-mini/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── model/
│   ├── view/
│   ├── controller/
│   ├── platform/
│   │   └── v4l2/
│   └── storage/
└── third_party/
    └── zxing-cpp/
    
    
