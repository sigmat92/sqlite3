cmake_minimum_required(VERSION 3.16)
project(RotaryQt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(rotary_qt
    main.cpp
    MainWindow.cpp
    MainWindow.h
)

target_link_libraries(rotary_qt PRIVATE Qt6::Widgets)

