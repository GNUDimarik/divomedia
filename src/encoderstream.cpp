/*****************************************************************************
 * encoderstream.cpp
 *
 * Created: 02.10.2020 2020 by Dmitry Adzhiev <dmitry.adjiev@gmail.com>
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
#include <encoderstream.h>
#include <utils/deleter.h>
#include <utils/log.h>

using namespace divomedia;
using namespace divomedia::utils;

EncoderStream::EncoderStream(AVCodecID encoder) : BasicStream(kOut) {
  if (encoder != AV_CODEC_ID_NONE) {
    open(encoder);
  }
}

bool EncoderStream::open(AVCodecID encoder) {
  AVCodec* codec = avcodec_find_encoder(encoder);

  if (codec != nullptr) {
    AVCodecContext* codecContext = avcodec_alloc_context3(codec);

    // TODO: Implement way to configure this before open
    if (codecContext != nullptr) {
      // Default parameters here:
      if (codec->type == AVMEDIA_TYPE_VIDEO) {
        // bit rate
        codecContext->bit_rate = 400000;
        // resolution must be a multiple of two
        codecContext->width = 640;
        codecContext->height = 480;
        // fps
        codecContext->time_base = AVRational{1, 25};
        codecContext->framerate = AVRational{25, 1};

        codecContext->gop_size = 10;
        codecContext->max_b_frames = 1;
        codecContext->pix_fmt = AV_PIX_FMT_YUV420P;
      }
      // TODO: put parameters for audio here

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
           avcodec_get_name(encoder));
    }
  } else {
    LOGE("Could not open codec '%s'\n", avcodec_get_name(encoder));
  }

  return false;
}

AVCodecContext* EncoderStream::avCodecContext() const {
  return mSpCodecContext.get();
}

EncoderStream& EncoderStream::operator<<(const Frame& frame) {
  if (isOpen()) {
    int ret = avcodec_send_frame(mSpCodecContext.get(), frame.avFrame());
    setState(ret >= 0 ? kOk : kFail);

    if (ret < 0) {
      LOGE("Could not send frame to codec. Error: '%s'\n",
           Utils::avErrorToString(AVERROR(ret)).c_str());
    }
  }
  return *this;
}

EncoderStream& EncoderStream::operator>>(std::shared_ptr<AVPacket>& pkt) {
  if (isOpen()) {
    int ret = 0;
    setState(kOk);

    while (ret >= 0) {
      ret = avcodec_receive_packet(mSpCodecContext.get(), pkt.get());
      if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
        break;
      } else if (ret < 0) {
        setState(kFail);
        LOGE("Error during encoding. Error '%s'\n",
             Utils::avErrorToString(AVERROR(ret)).c_str());
        break;
      }
    }
  }
  return *this;
}
