cmake_minimum_required(VERSION 3.16)
project(WaveformGenerator)

set(CMAKE_CXX_STANDARD 17)

# Add source directory to include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(WaveformGenerator
	    main.cpp
	        mainwindow.cpp
		    waveformwidget.cpp
		        mainwindow.ui
			    waveformwidget.h
			        mainwindow.h
				)

			target_link_libraries(WaveformGenerator PRIVATE Qt6::Widgets)

