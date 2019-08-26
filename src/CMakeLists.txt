set(SRCS
    cone1
    cone2
    cone3
    cone4
    cone5
    cone6
    hello
    cylinder
    cylinder_texture
    cylinder_light
    reference_count
    smart_pointer
    rtti
    debug_warning
    observer_command
	arrays
	xml_poly_data_read
	xml_poly_data_write
	ply_reader
    )

foreach(name ${SRCS})
    add_executable(${name} MACOSX_BUNDLE ${name}.cpp)
    target_link_libraries(${name} ${VTK_LIBRARIES})
endforeach()

add_subdirectory(qvtk_cylinder)
