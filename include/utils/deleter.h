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
        av_frame_unref(frame);
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
