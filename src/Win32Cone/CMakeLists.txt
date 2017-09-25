project(Win32Cone)

if(NOT VTK_BINARY_DIR)
	find_package(VTK)
	if(NOT VTK_DIR)
		message(FATAL_ERROR "Please set VTK_DIR.")
	endif()
	include(${VTK_USE_FILE})
endif()

add_executable(Win32Cone WIN32 Win32Cone.cxx)

target_link_libraries(Win32Cone ${VTK_LIBRARIES})
