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
