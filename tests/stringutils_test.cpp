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

#include <utils/stringutils.h>
#include "gtest/gtest.h"

using namespace divomedia::utils;

TEST(stringutils, toUpper) {
  std::string str = "test";
  ASSERT_EQ(StringUtils::toUpper(str), "TEST");
}

TEST(stringutils, toLower) {
  std::string str = "TEST";
  ASSERT_EQ(StringUtils::toLower(str), "test");
}

TEST(stringutils, containsString) {
  std::string str = "this is a test string";
  ASSERT_EQ(StringUtils::contains(str, "test"), true);
  ASSERT_EQ(StringUtils::contains(str, "teSt"), false);
}

TEST(stringutils, containsChar) {
  std::string str = "this is a test string";
  ASSERT_EQ(StringUtils::contains(str, 't'), true);
  ASSERT_EQ(StringUtils::contains(str, 'T'), false);
}

TEST(stringutils, split) {
  std::string str = "this is a test string";
  std::vector<std::string> vs = StringUtils::split(str, ' ');
  ASSERT_TRUE(vs.size() == 5);
  ASSERT_TRUE(vs[0] == "this");
  ASSERT_TRUE(vs[1] == "is");
  ASSERT_TRUE(vs[2] == "a");
  ASSERT_TRUE(vs[3] == "test");
  ASSERT_TRUE(vs[4] == "string");
}

TEST(stringutils, rtrim) {
  std::string str = "this is a test string    ";
  ASSERT_EQ(StringUtils::rtrim(str), "this is a test string");
}

TEST(stringutils, ltrim) {
  std::string str = "    this is a test string";
  ASSERT_EQ(StringUtils::ltrim(str), "this is a test string");
}

TEST(stringutils, trim) {
  std::string str = "    this is a test string    ";
  ASSERT_EQ(StringUtils::trim(str), "this is a test string");
}

TEST(stringutils, endsWith) {
  std::string str = "this is a test string";
  ASSERT_TRUE(StringUtils::endsWith(str, "string"));
  ASSERT_TRUE(StringUtils::endsWith(str, 'g'));
}

TEST(stringutils, startsWith) {
  std::string str = "this is a test string";
  ASSERT_TRUE(StringUtils::startsWith(str, "this"));
  ASSERT_TRUE(StringUtils::startsWith(str, 't'));
}
