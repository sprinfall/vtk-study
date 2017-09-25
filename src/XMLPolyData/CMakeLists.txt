project(XMLPolyData)

set(RENDERING_SRCS
    XMLPolyData_Read
    XMLPolyData_Write
    )

foreach(name ${RENDERING_SRCS})
    add_executable(${name} MACOSX_BUNDLE ${name}.cxx)
    target_link_libraries(${name} ${VTK_LIBRARIES})
endforeach()

