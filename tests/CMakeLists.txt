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
    divomedia
    ${AVDEVICE_LIBRARY}
    ${AVFORMAT_LIBRARY}
    ${AVFFILTER_LIBRARY}
    ${AVCODEC_LIBRARY}
    ${SWRESAMPLE_LIBRARY}
    ${SWSCALE_LIBRARY}
    ${POSTPROC_LIBRARY}
    ${AVUTIL_LIBRARY}
    m
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

