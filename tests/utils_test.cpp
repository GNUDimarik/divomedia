/*****************************************************************************
 * utils_test.cpp
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
#include <utils/utils.h>
#include <cstring>
#include "gtest/gtest.h"

using namespace divomedia::utils;

TEST(utils, path) { ASSERT_TRUE(!Utils::path().empty()); }
TEST(utils, binaryPath) {
#ifdef DIVO_MEDIA_OS_WINDOWS
  std::string cmd = "dir";
#else
  std::string cmd = "ls";
#endif

  ASSERT_TRUE(!Utils::binaryPath(cmd).empty());
}

TEST(utils, codecsEnumeration) {
  ASSERT_TRUE(!Utils::availableCodecs().empty());
}

TEST(utils, filtersEnumeration) {
  ASSERT_TRUE(!Utils::availableFilters().empty());
}

TEST(utils, optionsToDict) {
  std::unordered_map<std::string, std::string> opts = {{"key", "value"},
                                                       {"key1", "value1"}};
  std::shared_ptr<AVDictionary> dict = Utils::optionsToDict(opts);
  AVDictionaryEntry *entry = nullptr;
  entry = av_dict_get(dict.get(), "key", entry,
                      AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);
  ASSERT_TRUE(std::strcmp(entry->key, "key") == 0);
  ASSERT_TRUE(std::strcmp(entry->value, "value") == 0);
  entry = nullptr;
  entry = av_dict_get(dict.get(), "key1", entry,
                      AV_DICT_DONT_STRDUP_KEY | AV_DICT_DONT_STRDUP_VAL);
  ASSERT_TRUE(std::strcmp(entry->key, "key1") == 0);
  ASSERT_TRUE(std::strcmp(entry->value, "value1") == 0);
}
