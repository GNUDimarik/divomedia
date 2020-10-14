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
