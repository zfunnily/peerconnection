cmake_minimum_required(VERSION 2.8)
PROJECT(Server)
SET(PROJECT_OUTNAME Server)

if(WIN32)
    set(WEBRTC_LIBRARIES_DEBUG
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
        debug ${WEBRTC_LIB_DIR}/webrtc.lib
        debug ${WEBRTC_LIB_DIR}/third_party/jsoncpp/jsoncpp/json_reader.obj
        debug ${WEBRTC_LIB_DIR}/third_party/jsoncpp/jsoncpp/json_writer.obj
        debug ${WEBRTC_LIB_DIR}/third_party/jsoncpp/jsoncpp/json_value.obj
		debug ${WEBRTC_LIB_DIR}/rtc_tools/command_line_parser/simple_command_line_parser.obj
		
    )
    set(WEBRTC_LIBRARIES_RELEASE
        optimized ${WEBRTC_LIB_DIR}/webrtc.lib
        optimized ${WEBRTC_LIB_DIR}/third_party/jsoncpp/jsoncpp/json_reader.obj
        optimized ${WEBRTC_LIB_DIR}/third_party/jsoncpp/jsoncpp/json_writer.obj
        optimized ${WEBRTC_LIB_DIR}/third_party/jsoncpp/jsoncpp/json_value.obj
		optimized ${WEBRTC_LIB_DIR}/rtc_tools/command_line_parser/simple_command_line_parser.obj
    )
	set(PROJECT_SOURCES  main.cc
        data_socket.cc
        peer_channel.cc
        utils.cc
        test/field_trial.cc )
elseif(APPLE)

    set(WEBRTC_LIBRARIES_DEBUG
        debug ${WEBRTC_LIB_DIR}/libwebrtc.a
        debug ${WEBRTC_LIB_DIR}/rtc_tools/libcommand_line_parser.a
    )
    set(WEBRTC_LIBRARIES_RELEASE
        optimized ${WEBRTC_LIB_DIR}/libwebrtc.a
        optimized ${WEBRTC_LIB_DIR}/rtc_tools/libcommand_line_parser.a
    )
	set(PROJECT_SOURCES  main.cc
        data_socket.cc
        peer_channel.cc
        utils.cc
        test/field_trial.cc
		)
elseif(UNIX)

    set(WEBRTC_LIBRARIES_DEBUG
        debug ${WEBRTC_LIB_DIR}/libwebrtc.a
        debug ${WEBRTC_LIB_DIR}/rtc_tools/libcommand_line_parser.a
    )
    set(WEBRTC_LIBRARIES_RELEASE
        optimized ${WEBRTC_LIB_DIR}/libwebrtc.a
        optimized ${WEBRTC_LIB_DIR}/rtc_tools/libcommand_line_parser.a
    )
	set(PROJECT_SOURCES  main.cc
        data_socket.cc
        peer_channel.cc
        utils.cc
        test/field_trial.cc
		)
endif ()


include(FindLibraries)
include_directories(
${WEBRTC_INCLUDE_DIR}/
${WEBRTC_INCLUDE_DIR}/third_party/abseil-cpp
${WEBRTC_INCLUDE_DIR}/third_party/libyuv/include
${WEBRTC_INCLUDE_DIR}/third_party/jsoncpp/source/include
${GTK3_INCLUDE_DIRS}
)
message("LIBWEBRTC_LIBRARIES: ${LIBWEBRTC_LIBRARIES}")

add_executable(${PROJECT_OUTNAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_OUTNAME} ${WEBRTC_LIBRARIES_DEBUG} ${WEBRTC_LIBRARIES_RELEASE})
