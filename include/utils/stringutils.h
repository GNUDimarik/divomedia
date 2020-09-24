/*****************************************************************************
 * StringUtils.h
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
#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <vector>

__BEGIN_DECLS
#include <libavutil/error.h>
__END_DECLS

namespace divomedia {
namespace utils {

class StringUtils {
 public:
  static std::string toUpper(const std::string &str);
  static std::string toLower(const std::string &str);
  static bool contains(const std::string &str, const std::string &substr);
  static bool contains(const std::string &str,
                       const std::string::traits_type::char_type c);
  static std::vector<std::string> split(
      const std::string &str,
      const std::string::traits_type::char_type delimeter);
  static std::string rtrim(const std::string &str);
  static std::string ltrim(const std::string &str);
  static std::string trim(const std::string &str);
  static bool endsWith(const std::string &str, const std::string &substr);
  static bool endsWith(const std::string &str,
                       std::string::traits_type::char_type c);
  static bool startsWith(const std::string &str,
                         std::string::traits_type::char_type c);
  static bool startsWith(const std::string &str, const std::string &substr);
};

}  // namespace utils
}  // namespace divomedia
#endif  // STRINGUTILS_H
