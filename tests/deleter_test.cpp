/*****************************************************************************
 * deleter_test.cpp
 *
 * Created: 20.09.2020 2020 by Dmitry Adzhiev <dmitry.adjiev@gmail.com>
 *
 * Copyright 2020 Dmitry Adzhiev <dmitry.adjiev@gmail.com>. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/

#include <config.h>
#include <utils/deleter.h>
#include <type_traits>
#include "gtest/gtest.h"

using namespace divomedia::utils;

TEST(deleter, AVFormatContext) {
  std::function<void(AVFormatContext*)> func([](AVFormatContext*) {});
  auto deleter = Deleter<AVFormatContext>::create();
  bool val = std::is_same<decltype(deleter), decltype(func)>::value;
  ASSERT_TRUE(val);
}

TEST(deleter, AVDictionary) {
  std::function<void(AVDictionary*)> func([](AVDictionary*) {});
  auto deleter = Deleter<AVDictionary>::create();
  bool val = std::is_same<decltype(deleter), decltype(func)>::value;
  ASSERT_TRUE(val);
}

TEST(deleter, AVPacket) {
  std::function<void(AVPacket*)> func([](AVPacket*) {});
  auto deleter = Deleter<AVPacket>::create();
  bool val = std::is_same<decltype(deleter), decltype(func)>::value;
  ASSERT_TRUE(val);
}

TEST(deleter, AVCodecContext) {
  std::function<void(AVCodecContext*)> func([](AVCodecContext*) {});
  auto deleter = Deleter<AVCodecContext>::create();
  bool val = std::is_same<decltype(deleter), decltype(func)>::value;
  ASSERT_TRUE(val);
}

TEST(deleter, AVCodecParameters) {
  std::function<void(AVCodecParameters*)> func([](AVCodecParameters*) {});
  auto deleter = Deleter<AVCodecParameters>::create();
  bool val = std::is_same<decltype(deleter), decltype(func)>::value;
  ASSERT_TRUE(val);
}

TEST(deleter, AVFrame) {
  std::function<void(AVFrame*)> func([](AVFrame*) {});
  auto deleter = Deleter<AVFrame>::create();
  bool val = std::is_same<decltype(deleter), decltype(func)>::value;
  ASSERT_TRUE(val);
}

TEST(deleter, _SwsContext) {
  std::function<void(SwsContext*)> func([](SwsContext*) {});
  auto deleter = Deleter<SwsContext>::create();
  bool val = std::is_same<decltype(deleter), decltype(func)>::value;
  ASSERT_TRUE(val);
}

TEST(deleter, AVFilterGraph) {
  std::function<void(AVFilterGraph*)> func([](AVFilterGraph*) {});
  auto deleter = Deleter<AVFilterGraph>::create();
  bool val = std::is_same<decltype(deleter), decltype(func)>::value;
  ASSERT_TRUE(val);
}

TEST(deleter, AVFilterInOut) {
  std::function<void(AVFilterInOut*)> func([](AVFilterInOut*) {});
  auto deleter = Deleter<AVFilterInOut>::create();
  bool val = std::is_same<decltype(deleter), decltype(func)>::value;
  ASSERT_TRUE(val);
}

TEST(deleter, _SwrContext) {
  std::function<void(SwrContext*)> func([](SwrContext*) {});
  auto deleter = Deleter<SwrContext>::create();
  bool val = std::is_same<decltype(deleter), decltype(func)>::value;
  ASSERT_TRUE(val);
}

TEST(deleter, _AVCodecParserContext) {
  std::function<void(AVCodecParserContext*)> func([](AVCodecParserContext*) {});
  auto deleter = Deleter<AVCodecParserContext>::create();
  bool val = std::is_same<decltype(deleter), decltype(func)>::value;
  ASSERT_TRUE(val);
}
