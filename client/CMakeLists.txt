

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


include(FindLibraries)
include_directories(
${WEBRTC_INCLUDE_DIR}/
${WEBRTC_INCLUDE_DIR}/third_party/abseil-cpp
${WEBRTC_INCLUDE_DIR}/third_party/libyuv/include
${WEBRTC_INCLUDE_DIR}/third_party/jsoncpp/source/include
${GTK3_INCLUDE_DIRS}
)
message("LIBWEBRTC_LIBRARIES: ${LIBWEBRTC_LIBRARIES}")




add_executable(client "")
target_sources(client PRIVATE linux/main.cc
            linux/main_wnd.cc
            conductor.cc
            defaults.cc
            peer_connection_client.cc
            test/vcm_capturer.cc
            test/test_video_capturer.cc
            test/field_trial.cc
            strings/json.cc
)
message("WEBRTC_LIBRARIES_DEBUG: ${WEBRTC_LIBRARIES_DEBUG}")
message("WEBRTC_LIBRARIES_RELEASE: ${WEBRTC_LIBRARIES_RELEASE}")
message("WEBRTC_LIBRARIES: ${WEBRTC_LIBRARIES}")
message("GTK3_LIBRARIES: ${GTK3_LIBRARIES}")
message("JSONCPP_LIBRARIES: ${JSONCPP_LIBRARIES}")
message("JSONCPP: ${JSONCPP}")

target_include_directories(client PRIVATE ${GTK3_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(client ${GTK3_LIBRARIES} ${LIBWEBRTC_LIBRARIES} ${WEBRTC_LIBRARIES_DEBUG} ${WEBRTC_LIBRARIES_RELEASE})