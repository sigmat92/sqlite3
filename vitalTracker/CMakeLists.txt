cmake_minimum_required(VERSION 3.16)
project(VitalTracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(
    ${CMAKE_SOURCE_DIR}/model
    ${CMAKE_SOURCE_DIR}/view
    ${CMAKE_SOURCE_DIR}/controller
)

set(SOURCES
    main.cpp
    model/VitalModel.cpp
    view/MainWindow.cpp
    view/WaveformWidget.cpp
    controller/VitalController.cpp
)

qt_add_executable(VitalTracker ${SOURCES})

target_link_libraries(VitalTracker PRIVATE Qt6::Widgets)

