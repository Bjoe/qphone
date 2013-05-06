
if(CMAKE_CROSSCOMPILING)
    include(Coverage)
endif(CMAKE_CROSSCOMPILING)

find_package(QtTestUtil)

set(CMAKE_AUTOMOC OFF)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/testconfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/testconfig.h"
  )

include_directories(
    "../src"
    "${CMAKE_CURRENT_BINARY_DIR}/../src"
    "${QT_TEST_UTIL_INCLUDE_DIRS}"
)

set(test_additional_lib
    qphone
    ${QT_TEST_UTIL_LIBRARIES}
    ${QT_GUI_TEST_UTIL_LIBRARIES}
)

#set(test_additional
#    foo.cpp
#)

qt_test(foo exampletest.cpp)

