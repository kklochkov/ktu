cmake_minimum_required(VERSION 2.8)

project(PHP-KTU)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

set(QTDIR /Users/spirit/QtSDK/Desktop/Qt/474/gcc/)
set(QT_INCLUDE_DIR ${QTDIR}/include)
set(QT_LIBRARY_DIR ${QTDIR}/lib)
set(QT_QMAKE_EXECUTABLE ${QTDIR}/bin/qmake)
find_package(Qt4 REQUIRED)

INCLUDE_DIRECTORIES (${QT_INCLUDES})

include(FindPHP5)

if(NOT PHP5_FOUND)
    message(FATAL_ERROR "PHP5 could not be found!")
endif(NOT PHP5_FOUND)

add_subdirectory(src)
