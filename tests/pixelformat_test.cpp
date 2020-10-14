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

#include <pixelformat.h>

#include "gtest/gtest.h"

using namespace divomedia;

TEST(pixelformat, none) {
  PixelFormat fmt;
  ASSERT_EQ(fmt.toAvPixelFormat(), AV_PIX_FMT_NONE);
  ASSERT_TRUE(fmt.isNone());
}

TEST(pixelformat, ctor) {
  PixelFormat fmt;
  fmt = AV_PIX_FMT_RGB0;
  ASSERT_EQ(fmt.toAvPixelFormat(), AV_PIX_FMT_RGB0);
  PixelFormat fmt1(AV_PIX_FMT_RGB0);
  ASSERT_EQ(fmt1, AV_PIX_FMT_RGB0);
}

TEST(pixelformat, equals) {
  PixelFormat fmt;
  PixelFormat fmt1(AV_PIX_FMT_RGB0);
  fmt = AV_PIX_FMT_RGB0;
  ASSERT_EQ(fmt, fmt1);
  ASSERT_EQ(fmt.toAvPixelFormat(), fmt1.toAvPixelFormat());
  ASSERT_EQ(fmt, AV_PIX_FMT_RGB0);
}

TEST(pixelformat, not_equals) {
  PixelFormat fmt;
  PixelFormat fmt1(AV_PIX_FMT_RGB0);
  ASSERT_TRUE(fmt != fmt1);
  ASSERT_TRUE(fmt.toAvPixelFormat() != fmt1.toAvPixelFormat());
  ASSERT_TRUE(fmt != AV_PIX_FMT_RGB0);
}

TEST(pixelformat, toString) {
  PixelFormat fmt(AV_PIX_FMT_RGB0);
  PixelFormat fmt1(AV_PIX_FMT_RGB0);
  ASSERT_EQ(fmt.toString(), fmt1.toString());
}
