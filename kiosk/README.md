✅ Qt 6 Widgets
✅ MVC
✅ V4L2 only (no QtMultimedia)
✅ NO libjpeg
✅ NO YUYV
✅ GRAY8 only (best for ZXing)
✅ SQLite3 storage
✅ USB camera
✅ i.MX93 / Yocto friendly

STEP 0 — What we are building (mental model)
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
