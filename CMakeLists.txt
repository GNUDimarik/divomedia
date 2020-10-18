cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(divomedia)
set (DIVOMEDIA_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include")
set (CMAKE_CXX_FLAGS "-D__STDC_CONSTANT_MACROS -fPIC -pedantic -Wall -Wextra -Wcast-align -Wcast-qual  -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Werror -Wno-unused")
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
  "src/filtergraph.cpp"
  "src/buffersource.cpp"
  "src/buffersink.cpp"
  "src/frame.cpp"
  "src/image.cpp"
  "include/pixelformat.h"
  "include/size.h"
  "include/divomedia.h"
  "include/basicstream.h"
  "include/ifilestream.h"
  "include/decoderstream.h"
  "include/encoderstream.h"
  "include/filterstream.h"
  "include/filter.h"
  "include/filtergraph.h"
  "include/frame.h"
  "include/image.h"
  "include/config.h"
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
#set(PLATFORM_LIBRARIES_LIST z m lzma va va-drm va-x11 xcb xcb-shm xcb-shape xcb-xfixes asound SDL2 sndio Xv X11 Xext opus x264 x265 vpx)
endif (UNIX)

add_test(${PROJECT_NAME} ${UNIT_TEST} COMMAND ${UNIT_TEST})

find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)
find_library(AVDEVICE_LIBRARY avdevice)
find_library(AVFORMAT_LIBRARY avformat)
find_library(AVFFILTER_LIBRARY avfilter)
find_library(AVCODEC_LIBRARY avcodec)
find_library(SWRESAMPLE_LIBRARY swresample)
find_library(SWSCALE_LIBRARY swscale)
find_library(POSTPROC_LIBRARY postproc)
find_library(AVUTIL_LIBRARY avutil)
include_directories(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT}
                      ${AVDEVICE_LIBRARY}
                      ${AVFORMAT_LIBRARY}
                      ${AVFFILTER_LIBRARY}
                      ${AVCODEC_LIBRARY}
                      ${SWRESAMPLE_LIBRARY}
                      ${SWSCALE_LIBRARY}
                      ${POSTPROC_LIBRARY}
                      ${AVUTIL_LIBRARY}
                      ${PLATFORM_LIBRARIES_LIST}
                      m
                      stdc++fs)
