/*****************************************************************************
 * utils.cpp
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
#include <config.h>
#include <utils/deleter.h>
#include <utils/stringutils.h>
#include <utils/utils.h>
#include <algorithm>
#include <cstring>

__BEGIN_DECLS
#include <libavcodec/avcodec.h>
#include <libavutil/error.h>
__END_DECLS

using namespace divomedia::utils;

static constexpr const char *kPath = "PATH";

#ifdef DIVO_MEDIA_OS_WINDOWS
static constexpr int kSeparator = ';';
#else
static constexpr int kSeparator = ':';
#endif

std::string Utils::avErrorToString(int code) {
  char buffer[AV_ERROR_MAX_STRING_SIZE];
  av_strerror(code, buffer, AV_ERROR_MAX_STRING_SIZE);
  return std::string(buffer);
}

std::vector<fs::path> Utils::path() {
  std::string env = std::getenv(kPath);
  std::vector<fs::path> pathsList;

  if (!env.empty()) {
    std::vector<std::string> locations = StringUtils::split(env, kSeparator);
    std::copy(locations.begin(), locations.end(),
              std::back_inserter(pathsList));
  }

  return pathsList;
}

fs::path Utils::binaryPath(const std::string &command) {
  std::vector<fs::path> paths = path();
  fs::path path;

  for (auto &currentPath : paths) {
    if (fs::is_directory(currentPath)) {
      for (auto &dir : fs::recursive_directory_iterator(currentPath)) {
        if (StringUtils::endsWith(dir.path(),
                                  fs::path::preferred_separator + command)) {
          return dir.path();
        }
      }
    }
  }

  return path;
}

std::string Utils::strerror() {
#ifndef DIVO_MEDIA_OS_WINDOWS
  return std::strerror(errno);
#else
  size_t errmsglen = MAX_ERROR_LEN;
  char errmsg[MAX_ERROR_LEN];
  strerror_s(errmsg, errmsglen, errno);
  return errmsg;
#endif
}

std::vector<std::pair<std::string, divomedia::CodecKind>>
Utils::availableCodecs() {
  const AVCodec *codec = nullptr;
  void *pos = nullptr;
  std::vector<std::pair<std::string, divomedia::CodecKind>> codecs;

  while ((codec = av_codec_iterate(&pos))) {
    if (!pos) {
      continue;
    }  // AV_CODEC_CAP_EXPERIMENTAL

    CodecKind kind =
        av_codec_is_decoder(codec) ? CodecKind::kDecoder : CodecKind::kEncoder;

    std::pair<std::string, divomedia::CodecKind> pair =
        std::make_pair<>(codec->name, kind);
    codecs.emplace_back(pair);
  }

  return codecs;
}

std::vector<std::string> Utils::availableFilters() {
  const AVFilter *filter = nullptr;
  void *pos = nullptr;
  std::vector<std::string> filters;

  while ((filter = av_filter_iterate(&pos))) {
    filters.emplace_back(filter->name);
  }

  return filters;
}

std::shared_ptr<AVDictionary> Utils::optionsToDict(
    const std::unordered_map<std::string, std::string> &opt) {
  AVDictionary *dict = nullptr;

  for (std::pair<std::string, std::string> pair : opt) {
    av_dict_set(&dict, pair.first.c_str(), pair.second.c_str(), 0);
  }

  return std::move(
      std::shared_ptr<AVDictionary>(dict, Deleter<AVDictionary>::create()));
}

std::shared_ptr<AVPacket> Utils::createEmptyPacket() {
  return std::shared_ptr<AVPacket>(av_packet_alloc(),
                                   Deleter<AVPacket>::create());
}

std::shared_ptr<AVFrame> Utils::createEmptyFrame() {
  return std::shared_ptr<AVFrame>(av_frame_alloc(), Deleter<AVFrame>::create());
}

std::shared_ptr<AVFilterGraph> Utils::createFilterGraph() {
  return std::shared_ptr<AVFilterGraph>(avfilter_graph_alloc(),
                                        Deleter<AVFilterGraph>::create());
}
