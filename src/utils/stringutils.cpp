/*****************************************************************************
 * StringUtils.cpp
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
