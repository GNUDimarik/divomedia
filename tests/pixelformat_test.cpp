/*****************************************************************************
 * pixelformat.cpp
 *
 * Created: 11.09.2020 2020 by Dmitry Adzhiev <dmitry.adjiev@gmail.com>
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
