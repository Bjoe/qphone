cmake_minimum_required(VERSION 2.8.9)

project(QPhone)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" CACHE PATH "cmake modul path") 
include(BuildUtil)

# The version number.
set (Project_VERSION_MAJOR 0)
set (Project_VERSION_MINOR 1)
set (Project_VERSION_PATCH 0)

add_definitions(-std=c++11) # -fPIC -fPIE)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

#SET(ENV{PKG_CONFIG_PATH} "foo/bar/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
# find_package(PkgConfig)
# pkg_check_modules(FOO foo)
# include_directories(${FOO_INCLUDE_DIRS})
# link_directories(${FOO_LIBRARY_DIRS})

# cmake example from http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html
# Find the QtWidgets library
find_package(Qt5Core)

find_package(QpjSip)

#SET(ENV{PKG_CONFIG_PATH} "foo/bar/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
find_package(PkgConfig)
pkg_check_modules(PJSIP libpjproject)
link_directories(${PJSIP_LIBRARY_DIRS})

include_directories(
    "${QPJSIP_INCLUDE_DIRS}"
    "${PJSIP_INCLUDE_DIRS}"
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_BINARY_DIR}"
)

if(${DOC})
    find_doxygen()
endif(${DOC})

add_subdirectory(src)

if(${TEST})
    # The following are required to uses CTest, Dart and the Cdash dashboard
    enable_testing(true)
    include(CTest)
    add_subdirectory(tests)
endif(${TEST})
