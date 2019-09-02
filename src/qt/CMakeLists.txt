# 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
cmake_policy(SET CMP0071 NEW)

set(CMAKE_AUTOMOC ON)

if("${VTK_QT_VERSION}" STREQUAL "")
  message(FATAL_ERROR "VTK was not built with Qt")
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED QUIET)

add_subdirectory(cylinder)
add_subdirectory(image_viewer)
add_subdirectory(image_viewer2)
