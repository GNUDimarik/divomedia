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

#include <decoderstream.h>
#include <utils/deleter.h>
#include <utils/log.h>
#include <stdexcept>

using namespace divomedia;
using namespace divomedia::utils;

DecoderStream::DecoderStream(AVStream* stream) : BasicStream(kIn) {
  if (stream != nullptr) {
    open(stream->codecpar->codec_id,
         stream->codecpar->codec_type != AVMEDIA_TYPE_AUDIO);
  } else {
    LOGE("Input stream is NULL");
  }
}

AVCodecContext* DecoderStream::avCodecContext() const {
  return mSpCodecContext.get();
}

bool DecoderStream::open(AVCodecID decoder, bool openParser) {
  AVCodec* codec = avcodec_find_decoder(decoder);

  if (codec != nullptr) {
    if (openParser) {
      AVCodecParserContext* parser = av_parser_init(codec->id);

      if (parser != nullptr) {
        mSpParserContext.reset(parser, Deleter<AVCodecParserContext>::create());
      } else {
        LOGE("Could not open parser for codec '%s'. This is not fatal\n",
             avcodec_get_name(decoder));
      }
    }

    AVCodecContext* codecContext = avcodec_alloc_context3(codec);

    if (codecContext != nullptr) {
      mSpCodecContext.reset(codecContext, Deleter<AVCodecContext>::create());
      std::shared_ptr<AVDictionary> dict = optionsDictionary();
      AVDictionary* avDict = dict.get();
      int ret = avcodec_open2(codecContext, codec, &avDict);

      if (ret == 0) {
        setOpen(true);
        setState(kOk);
        return true;
      } else {
        LOGE("Could not open codec '%s'. Error: '%s'\n", codec->name,
             Utils::avErrorToString(AVERROR(ret)).c_str());
      }
    } else {
      LOGE("Could not init codec context for '%s'\n",
           avcodec_get_name(decoder));
    }
  } else {
    LOGE("Could not open codec '%s'\n", avcodec_get_name(decoder));
  }

  return false;
}

DecoderStream& DecoderStream::operator<<(const std::shared_ptr<AVPacket>& pkt) {
  if (isOpen()) {
    int ret = avcodec_send_packet(mSpCodecContext.get(), pkt.get());
    setState(ret >= 0 ? kOk : kFail);

    if (ret < 0) {
      LOGE("Could not send paket to codec. Error: '%s'\n",
           Utils::avErrorToString(AVERROR(ret)).c_str());
    }
  }
  return *this;
}

DecoderStream& DecoderStream::operator>>(Frame& frame) {
  if (isOpen()) {
    int ret = 0;
    setState(kOk);

    while (ret >= 0) {
      ret = avcodec_receive_frame(mSpCodecContext.get(), frame.avFrame());

      if (ret >= 0) {
        return *this;
      }

      if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
        break;
      } else if (ret < 0) {
        setState(kFail);
        LOGE("Error during decoding. Error '%s'\n",
             Utils::avErrorToString(AVERROR(ret)).c_str());
        break;
      }
    }
  }

  return *this;
}
