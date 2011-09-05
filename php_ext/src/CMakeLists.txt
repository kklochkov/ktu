cmake_minimum_required(VERSION 2.8)

set(LIB_CURRICULUMN_DIR /Users/spirit/projects/my/ktu/ktu)

include_directories(
    ${QT_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PHP5_INCLUDE_DIR}
    ${PHP5_MAIN_INCLUDE_DIR}
    ${PHP5_TSRM_INCLUDE_DIR}
    ${PHP5_ZEND_INCLUDE_DIR}
    ${PHP5_REGEX_INCLUDE_DIR}
    ${PHP5_EXT_INCLUDE_DIR}
    ${PHP5_DATE_INCLUDE_DIR}
    ${PHP5_STANDARD_INCLUDE_DIR}
    ${LIB_CURRICULUMN_DIR}/lib/libcurriculumn/include
    )

set(phpktu_LIB_SRCS
    php_ktu.cpp
    )

add_library(php_ktu MODULE ${phpktu_LIB_SRCS})

find_library(LIB_CURRICULUMN_LIBRARY curriculumn PATH ${LIB_CURRICULUMN_DIR}/bin)
if(NOT LIB_CURRICULUMN_LIBRARY)
    message(ERROR "libcurriculumn could not be found!")
endif(NOT LIB_CURRICULUMN_LIBRARY)

target_link_libraries(php_ktu ${QT_QTCORE_LIBRARY})
target_link_libraries(php_ktu ${LIB_CURRICULUMN_LIBRARY})
set_target_properties(php_ktu PROPERTIES PREFIX "")

if(APPLE)
    set_target_properties(php_ktu PROPERTIES PREFIX "" LINK_FLAGS ${CMAKE_SHARED_MODULE_CREATE_C_FLAGS} SUFFIX ".so" LINK_FLAGS "-undefined dynamic_lookup")
endif(APPLE)

install(TARGETS php_ktu DESTINATION ${PHP5_EXTENSION_DIR}/ )
