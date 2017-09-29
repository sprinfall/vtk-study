project(Win32Cone)

add_executable(Win32Cone WIN32 Win32Cone.cxx)

target_link_libraries(Win32Cone ${VTK_LIBRARIES})
