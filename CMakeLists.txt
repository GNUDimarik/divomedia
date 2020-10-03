cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(divomedia)
set (DIVOMEDIA_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include")
set (CMAKE_CXX_FLAGS "-D__STDC_CONSTANT_MACROS -fPIC")
set(ENABLE_TESTS true)

add_library(${PROJECT_NAME}
  "src/utils/stringutils.cpp"
  "include/utils/stringutils.h"
  "src/utils/utils.cpp"
  "include/utils/utils.h"
  "src/pixelformat.cpp"
  "src/main.cpp"
  "src/ifilestream.cpp"
  "src/decoderstream.cpp"
  "src/encoderstream.cpp"
  "src/filterstream.cpp"
  "src/filter.cpp"
  "src/buffersource.cpp"
  "src/buffersink.cpp"
  "src/frame.cpp"
  "include/pixelformat.h"
  "include/size.h"
  "include/divomedia.h"
  "include/basicstream.h"
  "include/ifilestream.h"
  "include/decoderstream.h"
  "include/encoderstream.h"
  "include/filterstream.h"
  "include/filter.h"
  "include/frame.h"
  "include/buffersource.h"
  "include/buffersink.h"
  "include/utils/deleter.h"
  "include/utils/log.h")

if(ENABLE_TESTS)
  include(cmake/googletest.cmake)
  fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
  )

enable_testing()
  add_subdirectory(tests)
endif()

if (WIN32)
  set(WINDOWS_LIBRARIES_LIST bcrypt ws2_32 secur32 strmiids vfw32 advapi32 shlwapi)
  set(PLATFORM_LIBRARIES_LIST ${WINDOWS_LIBRARIES_LIST})
endif (WIN32)

if (UNIX)
set(PLATFORM_LIBRARIES_LIST z m lzma va va-drm va-x11 xcb xcb-shm xcb-shape xcb-xfixes asound SDL2 sndio Xv X11 Xext)
endif (UNIX)

add_test(${PROJECT_NAME} ${UNIT_TEST} COMMAND ${UNIT_TEST})

find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)
include_directories(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/include"
                    "${FFMPEG_ROOT}/include")
link_directories("${FFMPEG_ROOT}/lib")
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT}
                      avdevice
                      avformat
                      avfilter
                      avcodec
                      swresample
                      swscale
                      postproc
                      avutil
                      ${PLATFORM_LIBRARIES_LIST}
                      stdc++fs)
