cmake_minimum_required(VERSION 3.16)

project(kiosk
    VERSION 1.0.0
    LANGUAGES C CXX
)

# --------------------------------------------------
# Build settings
# --------------------------------------------------
#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Explicitly disable OpenGL
set(QT_FEATURE_opengl OFF)
set(QT_FEATURE_opengles2 OFF)

# Reduce binary size (important for embedded)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# --------------------------------------------------
# Qt
# --------------------------------------------------
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

# --------------------------------------------------
# SQLite3 (from Yocto sysroot)
# --------------------------------------------------
find_package(SQLite3 REQUIRED)

# --------------------------------------------------
# ZXing (vendored)
# --------------------------------------------------
set(ZXING_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ZXING_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ZXING_USE_BUNDLED_ZINT OFF CACHE BOOL "" FORCE)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Disable ZXing extras
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(ZXING_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/zxing-cpp)
add_compile_definitions(ZX_USE_UTF8)

# --------------------------------------------------
# Source files
# --------------------------------------------------
set(SRC
    src/main.cpp

    # Models
    src/model/barcodemodel.h
    src/model/barcodemodel.cpp
    src/model/qrgenerator.h
    src/model/qrgenerator.cpp
    src/model/vitalsmodel.h
    src/model/vitalsmodel.cpp
    src/model/patient.h
    src/model/settingsmodel.h
    src/model/settingsmodel.cpp
    src/model/printserviceclient.h
    src/model/printserviceclient.cpp

    # Controllers
    src/controller/cameracontroller.h
    src/controller/cameracontroller.cpp
    src/controller/barcodescanner.h
    src/controller/barcodescanner.cpp
    src/controller/printcontroller.h
    src/controller/printcontroller.cpp
    src/controller/protocolparser.h
    src/controller/protocolparser.cpp
    src/controller/protocolcontroller.h
    src/controller/protocolcontroller.cpp
    src/controller/homecontroller.h
    src/controller/homecontroller.cpp
    src/controller/inputcontroller.h
    src/controller/visiontestcontroller.h
    src/controller/visiontestcontroller.cpp
    src/controller/settingscontroller.h
    src/controller/settingscontroller.cpp
    #src/controller/inputcontroller.cpp

    #service
    src/service/sessionservice.h
    src/service/sessionservice.cpp
    src/service/inputservice.h
    src/service/inputservice.cpp
    src/service/protocol.h
    src/service/vitalsservice.h
    src/service/vitalsservice.cpp
    src/service/settingsservice.h
    src/service/settingsservice.cpp
    src/service/systemsettingsservice.h
    src/service/systemsettingsservice.cpp
    src/service/adminauthservice.h
    src/service/adminauthservice.cpp
    
    # Platform
    src/platform/v4l2/v4l2camera.h
    src/platform/v4l2/v4l2camera.cpp
    src/platform/uart/uartdevice.h
    src/platform/uart/uartdevice.cpp
    src/platform/input/rotaryhandler.h
    src/platform/input/rotaryhandler.cpp

    # Storage
    #src/storage/sqliterecorder.h
    #src/storage/sqliterecorder.cpp
    src/storage/patientrepository.h
    src/storage/patientrepository.cpp
    src/storage/settingsrepository.h
    src/storage/settingsrepository.cpp
    src/storage/databasemanager.h
    src/storage/databasemanager.cpp
    src/storage/sessionrepository.h
    src/storage/sessionrepository.cpp
    src/storage/vitalsrepository.h
    src/storage/vitalsrepository.cpp
    
    # Views
    #src/view/mainwindow.h
    #src/view/mainwindow.cpp
    src/view/homeview.h
    src/view/homeview.cpp
    src/view/metriccard.h
    src/view/metriccard.cpp
    src/view/visiontestview.h
    src/view/visiontestview.cpp
    src/view/settingsview.h
    src/view/settingsview.cpp
)

# --------------------------------------------------
# Executable
# --------------------------------------------------
add_executable(kiosk ${SRC})

# --------------------------------------------------
# Include paths
# --------------------------------------------------
target_include_directories(kiosk
    PRIVATE
        src
        external/zxing-cpp/core
)

# --------------------------------------------------
# Link libraries
# --------------------------------------------------
target_link_libraries(kiosk
    PRIVATE
        Qt6::Widgets
        ZXing::ZXing
        SQLite::SQLite3
        Qt6::Network
	    
)

# --------------------------------------------------
# Compile definitions (optional tuning)
# --------------------------------------------------
#target_compile_definitions(kiosk
#    PRIVATE
#        QT_NO_KEYWORDS
#)

# --------------------------------------------------
# Warnings (safe for cross-compile)
# --------------------------------------------------
target_compile_options(kiosk
    PRIVATE
        -Wall
        -Wextra
        -Wno-unused-parameter
)

# --------------------------------------------------
# Install (Yocto friendly)
# --------------------------------------------------
install(TARGETS kiosk
        RUNTIME DESTINATION bin)
