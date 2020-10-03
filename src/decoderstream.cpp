/*****************************************************************************
 * decoderstream.cpp
 *
 * Created: 29.09.2020 2020 by Dmitry Adzhiev <dmitry.adjiev@gmail.com>
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
