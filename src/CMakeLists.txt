
set(QT_SRCS
    qphone.cpp
    qphonehandler.cpp
    call.cpp
    mainwindowcontroller.cpp
)

set(RESOURCES ../resources.qrc)

set(QML_PATH "${PROJECT_SOURCE_DIR}/assets/qml/main.qml")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/config.h"
  )

add_library(qphone STATIC ${QT_SRCS})
target_link_libraries(qphone Qt5::Widgets Qt5::Qml ${QPJSIP_LIBRARIES} ${PJSIP_LIBRARIES})

qt5_add_resources(QRC ${RESOURCES})
add_executable(phone main.cpp ${QRC})
target_link_libraries(phone qphone Qt5::Core Qt5::Widgets Qt5::Qml Qt5::Quick)
