project(Rendering)

set(RENDERING_SRCS
    Cylinder
    )

foreach(name ${RENDERING_SRCS})
    add_executable(Rendering_${name} MACOSX_BUNDLE ${name}.cxx)
    target_link_libraries(Rendering_${name} ${VTK_LIBRARIES})
endforeach()

