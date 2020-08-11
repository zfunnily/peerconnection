cmake_minimum_required(VERSION 3.5)
project(peerconnection)

add_definitions(-DQT_DEPRECATED_WARNINGS)
add_definitions(-DQT_NO_KEYWORDS)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    ${CMAKE_SOURCE_DIR}/CMakeModules)

add_definitions(-g -DWEBRTC_MAC -DWEBRTC_POSIX -fno-rtti)

set(WEBRTC_INCLUDE_DIR /Users/sources/C++/macos_webrtc/webrtc/src)
set(WEBRTC_ROOT_DIR /Users/sources/C++/macos_webrtc/webrtc/src/)
set(WEBRTC_LIB_DIR ${WEBRTC_ROOT_DIR}/out/mac/obj)
set(LIBWEBRTC_LIBRARIES ${WEBRTC_LIB_DIR})

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
PKG_CHECK_MODULES(JSONCPP REQUIRED jsoncpp)
add_definitions (${GTK3_CFLAGS_OTHER})


link_directories(/usr/local/opt/gettext/lib
                ${WEBRTC_LIB_DIR}
                ${WEBRTC_LIB_DIR}/sdk
                ${GTK3_LIBRARY_DIRS}
)
              
add_subdirectory(server)
add_subdirectory(client)
