cmake_minimum_required(VERSION 2.8)
project(Client)
SET(PROJECT_OUTNAME Client)
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

INCLUDE_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}/inc
)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_definitions(-DWEBRTC_EXTERNAL_JSON)

if (WIN32)
    set(WEBRTC_LIBRARIES_DEBUG
        debug ${WEBRTC_LIB_DIR}/webrtc.lib
        debug ${WEBRTC_LIB_DIR}/third_party/jsoncpp/jsoncpp/json_reader.obj
        debug ${WEBRTC_LIB_DIR}/third_party/jsoncpp/jsoncpp/json_writer.obj
        debug ${WEBRTC_LIB_DIR}/third_party/jsoncpp/jsoncpp/json_value.obj
		ws2_32.lib
		winmm.lib
		secur32.lib
		iphlpapi.lib
		crypt32.lib
		dmoguids.lib
		wmcodecdspuuid.lib
		amstrmid.lib
		msdmo.lib
		d3d11.lib
		dxgi.lib
    )
    set(WEBRTC_LIBRARIES_RELEASE
        optimized ${WEBRTC_LIB_DIR}/webrtc.lib
        optimized ${WEBRTC_LIB_DIR}/third_party/jsoncpp/jsoncpp/json_reader.obj
        optimized ${WEBRTC_LIB_DIR}/third_party/jsoncpp/jsoncpp/json_writer.obj
        optimized ${WEBRTC_LIB_DIR}/third_party/jsoncpp/jsoncpp/json_value.obj
		ws2_32.lib
		
		d3d11.lib
		dxgi.lib
		winmm.lib
		secur32.lib
		iphlpapi.lib
		crypt32.lib
		dmoguids.lib
		wmcodecdspuuid.lib
		amstrmid.lib
		msdmo.lib
    )

	set(PROJECT_SOURCES  main.cc
                main_wnd.cc
                conductor.cc
                defaults.cc
                peer_connection_client.cc
                test/vcm_capturer.cc
                test/test_video_capturer.cc
                test/field_trial.cc
                strings/json.cc 
			   )
	# ºöÂÔ¿â
	#SET(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:"msvcprtd.lib; libcmtd.lib")

elseif (APPLE)

    set(WEBRTC_LIBRARIES_DEBUG
        debug ${WEBRTC_LIB_DIR}/libwebrtc.a
        debug ${WEBRTC_LIB_DIR}/third_party/jsoncpp/libjsoncpp.a
        debug ${WEBRTC_LIB_DIR}/rtc_base/librtc_json_unittests.a
        debug ${WEBRTC_LIB_DIR}/rtc_base/librtc_base.a
        debug ${WEBRTC_LIB_DIR}/rtc_base/librtc_numerics.a
        debug ${WEBRTC_LIB_DIR}/rtc_base/libweak_ptr.a
    )
    set(WEBRTC_LIBRARIES_RELEASE
        optimized ${WEBRTC_LIB_DIR}/libwebrtc.a
        optimized ${WEBRTC_LIB_DIR}/third_party/jsoncpp/libjsoncpp.a
        optimized ${WEBRTC_LIB_DIR}/rtc_base/librtc_json_unittests.a
        optimized ${WEBRTC_LIB_DIR}/rtc_base/librtc_base.a
        optimized ${WEBRTC_LIB_DIR}/rtc_base/libweak_ptr.a
    )
	
    set(PROJECT_SOURCES  linux/main.cc
                linux/main_wnd.cc
                conductor.cc
                defaults.cc
                peer_connection_client.cc
                test/vcm_capturer.cc
                test/test_video_capturer.cc
                test/field_trial.cc
                strings/json.cc
    )
elseif (UNIX)
    set(WEBRTC_LIBRARIES_DEBUG
        debug ${WEBRTC_LIB_DIR}/libwebrtc.a
        debug ${WEBRTC_LIB_DIR}/third_party/jsoncpp/libjsoncpp.a
        debug ${WEBRTC_LIB_DIR}/rtc_base/librtc_json_unittests.a
        debug ${WEBRTC_LIB_DIR}/rtc_base/librtc_base.a
        debug ${WEBRTC_LIB_DIR}/rtc_base/librtc_numerics.a
        debug ${WEBRTC_LIB_DIR}/rtc_base/libweak_ptr.a
        debug ${WEBRTC_LIB_DIR}/third_party/jsoncpp/libjsoncpp.a
    )
    set(WEBRTC_LIBRARIES_RELEASE
        optimized ${WEBRTC_LIB_DIR}/libwebrtc.a
        optimized ${WEBRTC_LIB_DIR}/third_party/jsoncpp/libjsoncpp.a
        optimized ${WEBRTC_LIB_DIR}/rtc_base/librtc_json_unittests.a
        optimized ${WEBRTC_LIB_DIR}/rtc_base/librtc_base.a
        optimized ${WEBRTC_LIB_DIR}/rtc_base/libweak_ptr.a
    )

	set(PROJECT_SOURCES  linux/main.cc
		linux/main_wnd.cc
		conductor.cc
		defaults.cc
		peer_connection_client.cc
		test/vcm_capturer.cc
		test/test_video_capturer.cc
		test/field_trial.cc
		strings/json.cc )

	link_directories(/usr/local/opt/gettext/lib
            ${WEBRTC_LIB_DIR}
            ${WEBRTC_LIB_DIR}/sdk
            ${GTK3_LIBRARY_DIRS}
)
endif()

include(FindLibraries)
include_directories(
${WEBRTC_INCLUDE_DIR}/
${WEBRTC_INCLUDE_DIR}/third_party/abseil-cpp
${WEBRTC_INCLUDE_DIR}/third_party/libyuv/include
${WEBRTC_INCLUDE_DIR}/third_party/jsoncpp/source/include
${GTK3_INCLUDE_DIRS}
${PROJECT_SOURCE_DIR}/
${PROJECT_SOURCE_DIR}/test
${PROJECT_SOURCE_DIR}/strings
)
#file(GLOB_RECURSE HEAD_FILES ./*.h ./test/*.h ./strings/*.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_executable(${PROJECT_OUTNAME} ${PROJECT_SOURCES}) 
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_executable(${PROJECT_OUTNAME} WIN32  ${PROJECT_SOURCES})#WIN32 So the console window does not open on Windows
endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

IF (WIN32)
SET_TARGET_PROPERTIES(${PROJECT_OUTNAME} PROPERTIES LINK_FLAGS /MAP)
ENDIF(WIN32)


target_link_libraries(${PROJECT_OUTNAME} ${GTK3_LIBRARIES} ${LIBWEBRTC_LIBRARIES} ${WEBRTC_LIBRARIES_DEBUG} ${WEBRTC_LIBRARIES_RELEASE})
