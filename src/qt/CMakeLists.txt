foreach(p
    CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    )
if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
endif()
endforeach()

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

find_package(Qt5 COMPONENTS Widgets REQUIRED QUIET)

add_subdirectory(cylinder)
