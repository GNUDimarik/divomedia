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
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace divomedia::utils;

std::string StringUtils::toUpper(const std::string &str) {
  std::string ret;

  std::for_each(str.begin(), str.end(),
                [&ret](const std::string::traits_type::char_type &c) {
                  ret.push_back(static_cast<char>(std::toupper(c)));
                });

  return ret;
}

std::string StringUtils::toLower(const std::string &str) {
  std::string ret;

  std::for_each(str.begin(), str.end(),
                [&ret](const std::string::traits_type::char_type &c) {
                  ret.push_back(static_cast<char>(std::tolower(c)));
                });

  return ret;
}

bool StringUtils::contains(const std::string &str, const std::string &substr) {
  return str.find(substr) != std::string::npos;
}

bool StringUtils::contains(const std::string &str,
                           const std::string::traits_type::char_type c) {
  return str.find(static_cast<std::string::traits_type::char_type>(c)) !=
         std::string::npos;
}

std::vector<std::string> StringUtils::split(
    const std::string &str,
    const std::string::traits_type::char_type delimeter) {
  std::istringstream input(str);
  std::vector<std::string> result;
  std::string temp;

  while (std::getline(input, temp, (char)delimeter)) {
    result.emplace_back(temp);
  }

  return result;
}

std::string StringUtils::rtrim(const std::string &str) {
  std::string ret;

  if (!str.empty()) {
    auto i = str.rbegin();
    while (i != str.rend() && std::isspace(*i)) {
      ++i;
    }
    std::copy(str.begin(), i.base(), std::back_inserter(ret));
  }

  return ret;
}

std::string StringUtils::ltrim(const std::string &str) {
  std::string ret;

  if (!str.empty()) {
    auto i = str.begin();
    while (i != str.end() && std::isspace(*i++)) {
    }
    std::copy(--i, str.end(), std::back_inserter(ret));
  }

  return ret;
}

std::string StringUtils::trim(const std::string &str) {
  std::string ret = ltrim(str);
  return rtrim(ret);
}

bool StringUtils::startsWith(const std::string &str,
                             std::string::traits_type::char_type c) {
  if (!str.empty()) {
    return *str.begin() == c;
  }

  return false;
}

bool StringUtils::startsWith(const std::string &str,
                             const std::string &substr) {
  auto found = str.find(substr);
  return found == 0;
}

bool StringUtils::endsWith(const std::string &str,
                           std::string::traits_type::char_type c) {
  if (!str.empty()) {
    return *str.rbegin() == c;
  }

  return false;
}

bool StringUtils::endsWith(const std::string &str, const std::string &substr) {
  return str.compare(str.size() - substr.size(), substr.size(), substr) == 0;
}
