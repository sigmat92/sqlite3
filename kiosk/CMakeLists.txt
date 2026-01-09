cmake_minimum_required(VERSION 3.16)

project(kiosk
    VERSION 1.0.0
    LANGUAGES C CXX
)

# --------------------------------------------------
# Build settings
# --------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Reduce binary size (important for embedded)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# --------------------------------------------------
# Qt
# --------------------------------------------------
find_package(Qt6 REQUIRED COMPONENTS Widgets)

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

# --------------------------------------------------
# Source files
# --------------------------------------------------
set(SRC
    src/main.cpp

    # Models
    src/model/barcodemodel.h
    src/model/barcodemodel.cpp

    # Controllers
    src/controller/cameracontroller.h
    src/controller/cameracontroller.cpp
    src/controller/barcodescanner.h
    src/controller/barcodescanner.cpp

    # Platform
    src/platform/v4l2/v4l2camera.h
    src/platform/v4l2/v4l2camera.cpp

    # Storage
    src/storage/sqliterecorder.h
    src/storage/sqliterecorder.cpp

    # Views
    src/view/mainwindow.h
    src/view/mainwindow.cpp
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
