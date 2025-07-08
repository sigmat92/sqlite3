cmake_minimum_required(VERSION 3.16)
project(QtTest)

find_package(Qt6 COMPONENTS Core REQUIRED)

add_executable(test_app main.cpp)
target_link_libraries(test_app Qt6::Core)

