/*****************************************************************************
 * utils.h
 *
 * Created: 18.09.2020 2020 by Dmitry Adzhiev <dmitry.adjiev@gmail.com>
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
#ifndef UTILS_H
#define UTILS_H

#include <config.h>
#include <memory>

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
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
};

}  // namespace utils
}  // namespace divomedia
#endif  // UTILS_H
