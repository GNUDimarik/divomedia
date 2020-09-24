add_executable(
    unit_tests
    pixelformat_test.cpp
    stringutils_test.cpp
    utils_test.cpp
    size_test.cpp
    deleter_test.cpp
    ifstream_test.cpp
    )

target_link_libraries(
    unit_tests
    gtest_main
    ${FFMPEG_ROOT}/lib/libavdevice.a
    ${FFMPEG_ROOT}/lib/libavformat.a
    ${FFMPEG_ROOT}/lib/libavfilter.a
    ${FFMPEG_ROOT}/lib/libavcodec.a
    ${FFMPEG_ROOT}/lib/libswresample.a
    ${FFMPEG_ROOT}/lib/libswscale.a
    ${FFMPEG_ROOT}/lib/libavutil.a
    divomedia
    )

include_directories(${DIVOMEDIA_INCLUDE_PATH})

add_test(
  NAME
    unit_tests
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )

add_custom_command(
     TARGET unit_tests
     COMMENT "Run tests"
     POST_BUILD
     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
     COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/tests/unit_tests -C $<CONFIGURATION> -R "^${UNIT_TEST}$" --output-on-failures)

