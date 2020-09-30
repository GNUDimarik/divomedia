/*****************************************************************************
 * deleter.h
 *
 * Created: 19.09.2020 2020 by Dmitry Adzhiev <dmitry.adjiev@gmail.com>
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
#ifndef DELETER_H
#define DELETER_H

#include <config.h>
#include <functional>

__BEGIN_DECLS
#include <libavfilter/avfilter.h>
#include <libavformat/avformat.h>
#include <libavutil/dict.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
__END_DECLS

#include <iostream>

namespace divomedia {
namespace utils {
template <class T>
class Deleter;

template <>
class Deleter<AVFormatContext> {
 public:
  static std::function<void(AVFormatContext*)> create() {
    return std::function<void(AVFormatContext*)>([](AVFormatContext* ctx) {
      if (ctx) {
        avformat_free_context(ctx);
      }
    });
  }
};

template <>
class Deleter<AVDictionary> {
 public:
  static std::function<void(AVDictionary*)> create() {
    return std::function<void(AVDictionary*)>([](AVDictionary* dict) {
      if (dict) {
        av_dict_free(&dict);
        dict = nullptr;
      }
    });
  }
};

template <>
class Deleter<AVPacket> {
 public:
  static std::function<void(AVPacket*)> create() {
    return std::function<void(AVPacket*)>([](AVPacket* packet) {
      if (packet) {
        av_packet_free(&packet);
        packet = nullptr;
      }
    });
  }
};

template <>
class Deleter<AVCodecContext> {
 public:
  static std::function<void(AVCodecContext*)> create() {
    return std::function<void(AVCodecContext*)>([](AVCodecContext* ctx) {
      if (ctx) {
        avcodec_free_context(&ctx);
        ctx = nullptr;
      }
    });
  }
};

template <>
class Deleter<AVCodecParameters> {
 public:
  static std::function<void(AVCodecParameters*)> create() {
    return std::function<void(AVCodecParameters*)>(
        [](AVCodecParameters* params) {
          if (params) {
            avcodec_parameters_free(&params);
            params = nullptr;
          }
        });
  }
};

template <>
class Deleter<AVFrame> {
 public:
  static std::function<void(AVFrame*)> create() {
    return std::function<void(AVFrame*)>([](AVFrame* frame) {
      if (frame) {
        av_frame_free(&frame);
        frame = nullptr;
      }
    });
  }
};

template <>
class Deleter<SwsContext> {
 public:
  static std::function<void(SwsContext*)> create() {
    return std::function<void(SwsContext*)>([](SwsContext* ctx) {
      if (ctx) {
        sws_freeContext(ctx);
        ctx = nullptr;
      }
    });
  }
};

template <>
class Deleter<AVFilterGraph> {
 public:
  static std::function<void(AVFilterGraph*)> create() {
    return std::function<void(AVFilterGraph*)>([](AVFilterGraph* graph) {
      if (graph) {
        avfilter_graph_free(&graph);
        graph = nullptr;
      }
    });
  }
};

template <>
class Deleter<AVFilterInOut> {
 public:
  static std::function<void(AVFilterInOut*)> create() {
    return std::function<void(AVFilterInOut*)>([](AVFilterInOut* inOut) {
      if (inOut) {
        avfilter_inout_free(&inOut);
        inOut = nullptr;
      }
    });
  }
};

template <>
class Deleter<SwrContext> {
 public:
  static std::function<void(SwrContext*)> create() {
    return std::function<void(SwrContext*)>([](SwrContext* ctx) {
      if (ctx) {
        swr_free(&ctx);
        ctx = nullptr;
      }
    });
  }
};

template <>
class Deleter<AVInputFormat> {
 public:
  static std::function<void(AVInputFormat*)> create() {
    return std::function<void(AVInputFormat*)>([](AVInputFormat* ctx) {});
  }
};

template <>
class Deleter<AVCodecParserContext> {
 public:
  static std::function<void(AVCodecParserContext*)> create() {
    return std::function<void(AVCodecParserContext*)>(
        [](AVCodecParserContext* ctx) {
          if (ctx) {
            av_parser_close(ctx);
            ctx = nullptr;
          }
        });
  }
};
}  // namespace utils
}  // namespace divomedia
#endif  // DELETER_H
