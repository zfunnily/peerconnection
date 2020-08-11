cmake_minimum_required(VERSION 2.8)
project(peerconnection)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    ${CMAKE_SOURCE_DIR}/CMakeModules)

# UNICODE宏定义
add_definitions(-DUNICODE -D_UNICODE)


if (WIN32)
    SET(OUTPUT_PATH_DEBUG ${PROJECT_SOURCE_DIR}/../build/debug_windows_x64)
    SET(OUTPUT_PATH_RELEASE ${PROJECT_SOURCE_DIR}/../bin/windows_x64/im_common)
    SET(PROJECT_LIB_DIR_DEBUG ${PROJECT_SOURCE_DIR}/../build/debug_windows_x64)
    SET(PROJECT_LIB_DIR_RELEASE ${PROJECT_SOURCE_DIR}/../bin/windows_x64/im_common)

    set(WEBRTC_ROOT_DIR D:/Work/webrtc/webrtc/src)
    set(WEBRTC_LIB_DIR ${WEBRTC_ROOT_DIR}/out/win/obj)
	set(WEBRTC_LIB_PLAT ${WEBRTC_ROOT_DIR}/out/win)

	# 运行时库设置
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

	# 五个必要的宏定义
	add_definitions(-DWEBRTC_WIN)
	add_definitions(-DNOMINMAX)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
	add_definitions(-DWIN32_LEAN_AND_MEAN)

elseif (APPLE)
	SET(OUTPUT_PATH_DEBUG ${PROJECT_SOURCE_DIR}/../build/debug_macos_x64)
	SET(OUTPUT_PATH_RELEASE ${PROJECT_SOURCE_DIR}/../bin/macos_x64/im_common)
	SET(PROJECT_LIB_DIR_DEBUG ${PROJECT_SOURCE_DIR}/../build/debug_macos_x64)
	SET(PROJECT_LIB_DIR_RELEASE ${PROJECT_SOURCE_DIR}/../bin/macos_x64/im_common)

    set(WEBRTC_ROOT_DIR /Users/sources/C++/macos_webrtc/webrtc/src/)
    set(WEBRTC_LIB_DIR ${WEBRTC_ROOT_DIR}/out/mac/obj)
	add_definitions(-g -DWEBRTC_MAC -DWEBRTC_POSIX -fno-rtti)
elseif (UNIX)
	SET(OUTPUT_PATH_DEBUG ${PROJECT_SOURCE_DIR}/../build/debug_macos_x64)
	SET(OUTPUT_PATH_RELEASE ${PROJECT_SOURCE_DIR}/../bin/macos_x64/im_common)
	SET(PROJECT_LIB_DIR_DEBUG ${PROJECT_SOURCE_DIR}/../build/debug_macos_x64)
	SET(PROJECT_LIB_DIR_RELEASE ${PROJECT_SOURCE_DIR}/../bin/macos_x64/im_common)

    set(WEBRTC_ROOT_DIR /Users/sources/C++/macos_webrtc/webrtc/src/)
    set(WEBRTC_LIB_DIR ${WEBRTC_ROOT_DIR}/out/mac/obj)
	add_definitions(-g -DWEBRTC_MAC -DWEBRTC_POSIX -fno-rtti)
endif ()
set(WEBRTC_INCLUDE_DIR ${WEBRTC_ROOT_DIR})
set(LIBWEBRTC_LIBRARIES ${WEBRTC_LIB_DIR})

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_PATH_DEBUG})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_PATH_RELEASE})

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_PATH_DEBUG})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_PATH_RELEASE})
#上面两条语句分别设置了Debug版本和Release版本库文件的输出目录,

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_PATH_DEBUG})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_PATH_RELEASE})
#上面两条语句分别设置了Debug版本和Release版本可执行文件的输出目录,

#FIND_PACKAGE(PkgConfig REQUIRED)
#PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
#PKG_CHECK_MODULES(JSONCPP REQUIRED jsoncpp)
#add_definitions (${GTK3_CFLAGS_OTHER})


link_directories(/usr/local/opt/gettext/lib
                ${WEBRTC_LIB_DIR}
                ${WEBRTC_LIB_PLAT}
                ${WEBRTC_LIB_DIR}/sdk
                ${GTK3_LIBRARY_DIRS}
)
              
#add_subdirectory(test)
#add_subdirectory(strings)
add_subdirectory(server)
add_subdirectory(client)
