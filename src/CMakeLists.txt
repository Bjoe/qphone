
set(QT_SRCS
    qphone.cpp
    qphoneview.cpp
    acceptor.cpp
    call.cpp
)

set(QML_PATH "${PROJECT_SOURCE_DIR}/assets/main.qml")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/config.h"
  )

add_library(qphone STATIC ${QT_SRCS})
qt5_use_modules(qphone Core Quick)

add_executable(phone main.cpp)
target_link_libraries(phone qphone ${QPJSIP_LIBRARIES} ${PJSIP_LIBRARIES})
qt5_use_modules(phone Core Quick)
