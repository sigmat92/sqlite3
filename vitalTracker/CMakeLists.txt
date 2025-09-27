cmake_minimum_required(VERSION 3.16)
project(vitalTracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

add_executable(vitalTracker
    main.cpp
    mainwindow.cpp
    waveformview.cpp
    vitalmodel.cpp
    vitalcontroller.cpp
)

target_include_directories(vitalTracker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(vitalTracker Qt6::Core Qt6::Widgets Qt6::Gui)

