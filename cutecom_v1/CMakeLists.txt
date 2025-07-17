cmake_minimum_required(VERSION 3.16)
project(cutecom-serial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets SerialPort Sql)

add_executable(cutecom-serial
    main.cpp
    MainWindow.cpp MainWindow.h MainWindow.ui
    ConfigManager.cpp ConfigManager.h
    Logger.cpp Logger.h
    LogViewer.cpp LogViewer.h LogViewer.ui
)

target_link_libraries(cutecom-serial PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::SerialPort Qt6::Sql)

