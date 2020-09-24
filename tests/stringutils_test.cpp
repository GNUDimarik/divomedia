/*****************************************************************************
 * stringutils_test.cpp
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
