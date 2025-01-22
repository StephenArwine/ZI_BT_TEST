cmake_minimum_required(VERSION 3.5.0)
project(ZI_BT_TEST)
set (CMAKE_CXX_STANDARD 20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(SOURCES
    ZI.cpp
    log.cpp
    bluetooth.cpp
    btlib.c
    wifiConfig.cpp
    )
set(HEADERS
    ZI.hpp
    log.hpp
    bluetooth.hpp
    btlib.h
    wifiConfig.hpp
    )

add_executable(ZI_BT_TEST ${SOURCES} ${HEADERS})

target_link_libraries(ZI_BT_TEST -lpigpio)
