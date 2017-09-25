cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(vtk-study)

find_package(VTK REQUIRED)

# TODO
# if(NOT VTK_USE_RENDERING)
#     message(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
# endif(NOT VTK_USE_RENDERING)

message(STATUS "VTK use file:\t" ${VTK_USE_FILE})
message(STATUS "VTK include dir:\t" ${VTK_INCLUDE_DIRS})

include(${VTK_USE_FILE})

add_subdirectory(src/Arrays)
add_subdirectory(src/XMLPolyData)
add_subdirectory(src/Rendering)
add_subdirectory(src/Win32Cone)
