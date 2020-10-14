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
