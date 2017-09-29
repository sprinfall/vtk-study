cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(vtk-study)

find_package(VTK REQUIRED)
if(NOT VTK_DIR)
	message(FATAL_ERROR "Please set VTK_DIR.")
endif()
include(${VTK_USE_FILE})

message(STATUS "VTK use file:\t" ${VTK_USE_FILE})
message(STATUS "VTK include dir:\t" ${VTK_INCLUDE_DIRS})

add_subdirectory(src/Arrays)
add_subdirectory(src/XMLPolyData)
add_subdirectory(src/Rendering)
add_subdirectory(src/Cone)
add_subdirectory(src/Win32Cone)
