

set(WEBRTC_LIBRARIES_DEBUG
    debug ${WEBRTC_LIB_DIR}/libwebrtc.a
    debug ${WEBRTC_LIB_DIR}/rtc_tools/libcommand_line_parser.a
)
set(WEBRTC_LIBRARIES_RELEASE
optimized ${WEBRTC_LIB_DIR}/libwebrtc.a
optimized ${WEBRTC_LIB_DIR}/rtc_tools/libcommand_line_parser.a
)


include(FindLibraries)
include_directories(
${WEBRTC_INCLUDE_DIR}/
${WEBRTC_INCLUDE_DIR}/third_party/abseil-cpp
${WEBRTC_INCLUDE_DIR}/third_party/libyuv/include
${WEBRTC_INCLUDE_DIR}/third_party/jsoncpp/source/include
${GTK3_INCLUDE_DIRS}
)
message("LIBWEBRTC_LIBRARIES: ${LIBWEBRTC_LIBRARIES}")



add_executable(server "")
target_sources(server 
    PRIVATE
        main.cc
        data_socket.cc
        peer_channel.cc
        utils.cc
        test/field_trial.cc
)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(server ${LIBWEBRTC_LIBRARIES} ${WEBRTC_LIBRARIES_DEBUG} ${WEBRTC_LIBRARIES_RELEASE})