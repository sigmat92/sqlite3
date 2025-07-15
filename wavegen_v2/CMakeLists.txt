cmake_minimum_required(VERSION 3.14)
project(WaveformGenerator)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

qt_add_executable(WaveformGenerator
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    waveformwidget.cpp
    waveformwidget.h
    waveformdb.cpp
    waveformdb.h
)

target_link_libraries(WaveformGenerator PRIVATE Qt6::Widgets Qt6::Sql)