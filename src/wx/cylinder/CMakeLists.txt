set(TARGET_NAME wx_cylinder)

set(SRCS
    app.cpp
    my_panel.cpp
    my_panel.h
    my_frame.cpp
    my_frame.h
    )

add_executable(${TARGET_NAME} WIN32 MACOSX_BUNDLE ${SRCS})

target_link_libraries(${TARGET_NAME} ${wxWidgets_LIBRARIES})
target_link_libraries(${TARGET_NAME} ${VTK_LIBRARIES})
