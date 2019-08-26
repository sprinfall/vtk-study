cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
foreach(p
    CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    )
if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
endif()
endforeach()

project(qvtk_cylinder)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(VTK COMPONENTS
    vtkCommonCore
    vtkFiltersCore
    vtkInfovisCore
    vtkInteractionStyle
    vtkViewsQt
    # Adam added
    vtkRenderingContextOpenGL2
    vtkRenderingOpenGL2
    vtkRenderingGL2PSOpenGL2
  )

include(${VTK_USE_FILE})

if("${VTK_QT_VERSION}" STREQUAL "")
  message(FATAL_ERROR "VTK was not built with Qt")
endif()

# Use the include path and library for Qt that is used by VTK.
include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

set(SRCS
    main.cpp
    my_widget.cpp
    my_widget.h
    my_window.cpp
    my_window.h
    )

find_package(Qt5 COMPONENTS Widgets REQUIRED QUIET)

add_executable(qvtk_cylinder MACOSX_BUNDLE ${SRCS})

target_link_libraries(qvtk_cylinder Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(qvtk_cylinder ${VTK_LIBRARIES})
