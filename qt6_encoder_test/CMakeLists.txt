cmake_minimum_required(VERSION 3.16)
project(RotaryTestApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    rotaryhandler.cpp
    rotaryhandler.h
)

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets)

