
if(CMAKE_CROSSCOMPILING)
    include(Coverage)
endif(CMAKE_CROSSCOMPILING)

set(CMAKE_AUTOMOC OFF)

# cmake example from http://qt-project.org/doc/qt-5.1/qtdoc/cmake-manual.html
find_package(Qt5Test REQUIRED)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/testconfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/testconfig.h"
  )

include_directories(
    "../src"
    "${CMAKE_CURRENT_BINARY_DIR}/../src"
)

set(test_additional_lib
    qphone
    Qt5::Qml
    Qt5::Quick
)

#set(test_additional
#    foo.cpp
#)

qt_test(foo exampletest.cpp)
