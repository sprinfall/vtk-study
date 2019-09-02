set(TARGET_NAME qt_image_viewer)

project(${TARGET_NAME})

# Use the include path and library for Qt that is used by VTK.
include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

set(SRCS main.cpp)

add_executable(${TARGET_NAME} MACOSX_BUNDLE ${SRCS})

target_link_libraries(${TARGET_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(${TARGET_NAME} ${VTK_LIBRARIES})
