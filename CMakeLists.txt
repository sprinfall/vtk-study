cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(vtk-study)

# Find includes in corresponding build directories.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(ENABLE_QT "Build Qt examples" OFF)

find_package(VTK REQUIRED)
if(NOT VTK_DIR)
    message(FATAL_ERROR "Please set VTK_DIR.")
endif()
include(${VTK_USE_FILE})

message(STATUS "VTK use file:\t" ${VTK_USE_FILE})
message(STATUS "VTK include dir:\t" ${VTK_INCLUDE_DIRS})

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(ENABLE_QT)
	add_subdirectory(src)
endif()
