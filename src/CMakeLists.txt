
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/config.h"
  )

add_library(qphone)

target_sources(qphone
PRIVATE
    qphone.cpp
    qphonehandler.cpp
    call.cpp
    mainwindowcontroller.cpp
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/call.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/qphonehandler.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/mainwindowcontroller.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/qphone.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/config.h>

    $<INSTALL_INTERFACE:include/call.h>
    $<INSTALL_INTERFACE:include/qphonehandler.h>
    $<INSTALL_INTERFACE:include/mainwindowcontroller.h>
    $<INSTALL_INTERFACE:include/qphone.h>
    $<INSTALL_INTERFACE:include/config.h>
)

#set(QML_PATH "${PROJECT_SOURCE_DIR}/assets/qml/main.qml")

target_compile_features(qphone PUBLIC cxx_std_17)
target_link_libraries(qphone PUBLIC Qt5::Widgets Qt5::Quick Qt5::Qml QPjSIP::qpjsua)
target_include_directories(qphone
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
)
add_library(${namespace}::qphone ALIAS qphone)

qt5_add_resources(QRC ../resources.qrc)
add_executable(phone main.cpp ${QRC})
target_link_libraries(phone PUBLIC qphone)

install(FILES
    call.h
    qphonehandler.h
    mainwindowcontroller.h
    qphone.h
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS phone qphone
  EXPORT "${TARGETS_EXPORT_NAME}"
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

