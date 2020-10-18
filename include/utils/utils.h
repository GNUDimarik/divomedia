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

#ifndef UTILS_H
#define UTILS_H

#include <config.h>
#include <memory>

#if __cplusplus >= 201703L
#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif
#endif

__BEGIN_DECLS
#include <libavcodec/avcodec.h>
#include <libavfilter/avfilter.h>
#include <libavutil/dict.h>
__END_DECLS

#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

namespace divomedia {

enum CodecKind : std::uint8_t { kDecoder, kEncoder };

namespace utils {
/**
 * @brief The Utils class different utils for working with environment and other
 * things
 */
class Utils {
 public:
  /**
   * @brief avErrorToString
   * @param code AVERROR value
   * @return string representation of the error code got from ffmpeg libraries
   */
  static std::string avErrorToString(int code);
#if __cplusplus >= 201703L
  /**
   * @brief path splits content of PATH environment variable to vector
   * @return vector of items of PATH environment variable splitted by it's
   * separator which is ':' on unix based systems and ';' on windows
   */
  static std::vector<fs::path> path();
  /**
   * @brief binaryPath tries to find command in PATH
   * @param command
   * @return full path to command or empty path if it doesn't exist in PATH
   */
  static fs::path binaryPath(const std::string &command);
#endif
  /**
   * @brief strerror same as strerror from C library
   * @return string representation of errno error code
   */
  static std::string strerror();
  /**
   * @brief availableCodecs enumerates all available codecs
   * @return std::pair<std::pair<std::string, CodecKind>
   * you able to check codec kind like here:
   * @code
   * auto codecs = Utils::availableCodecs();
   *
   * if (!codecs.empty()) {
   *   if (codecs[0].second == CodecKind::kDecoder) {
   *     // ...
   *   }
   * }
   * @endcode
   */
  static std::vector<std::pair<std::string, CodecKind>> availableCodecs();
  static std::vector<std::string> availableFilters();
  static std::shared_ptr<AVDictionary> optionsToDict(
      const std::unordered_map<std::string, std::string> &opt);
  static std::shared_ptr<AVPacket> createEmptyPacket();
  static std::shared_ptr<AVFrame> createEmptyFrame();
  static std::shared_ptr<AVFilterGraph> createFilterGraph();
  static std::shared_ptr<AVFilterInOut> createInOut();
};

}  // namespace utils
}  // namespace divomedia
#endif  // UTILS_H
