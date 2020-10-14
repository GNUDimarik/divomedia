/*
 * Copyright 2020 Dmitry Adzhiev <dmitry.adjiev@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

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
