/*****************************************************************************
 * ifstream_test.cpp
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
#include <ifilestream.h>
#include <memory>
#include "gtest/gtest.h"

using namespace divomedia;

// This code refactored for using exceptions. So may be test should be rewritten

TEST(ifilestream, file_not_found_is_fail) {
  try {
    IFileStream istream("file not found", IFileStream::kIn);
    ASSERT_TRUE(istream.isFail());
  } catch (const std::exception &e) {
    ASSERT_TRUE(!std::string(e.what()).empty());
  }
}

TEST(ifilestream, file_not_found_is_not_ok) {
  try {
    IFileStream istream("file not found", IFileStream::kIn);
    ASSERT_FALSE(istream.isOk());
  } catch (const std::exception &e) {
    ASSERT_TRUE(!std::string(e.what()).empty());
  }
}
