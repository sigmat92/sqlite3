

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
    
    
