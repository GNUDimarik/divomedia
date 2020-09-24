/*****************************************************************************
 * size_test.cpp
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

#include <divomedia.h>
#include "gtest/gtest.h"

using namespace divomedia;

TEST(size, ctor) {
  Size<std::size_t> sz;
  ASSERT_TRUE(sz.isNull());
}

TEST(size, equality) {
  Size<std::size_t> sz(12, 24);
  Size<std::size_t> sz1(12, 24);
  ASSERT_TRUE(sz == sz1);
}

TEST(size, comparsion) {
  Size<std::size_t> sz(12, 24);
  Size<std::size_t> sz1(12, 25);
  ASSERT_TRUE(sz != sz1);
}

TEST(size, assigment) {
  Size<std::size_t> sz(12, 24);
  Size<std::size_t> sz1;
  sz1 = sz;
  ASSERT_TRUE(sz == sz1);
}

TEST(size, copyctor) {
  Size<std::size_t> sz(12, 24);
  Size<std::size_t> sz1(sz);
  sz1 = sz;
  ASSERT_TRUE(sz == sz1);
}

TEST(size, setters) {
  Size<std::size_t> sz;
  sz.setHeight(1);
  sz.setWidth(2);
  ASSERT_TRUE(sz.width() == 2);
  ASSERT_TRUE(sz.height() == 1);
}
