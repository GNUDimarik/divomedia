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
  return open(avcodec_get_name(encoder));
}

AVCodecContext* EncoderStream::avCodecContext() const {
  return mSpCodecContext.get();
}

bool EncoderStream::open(const std::string& encoderName) {
  AVCodec* codec = avcodec_find_encoder_by_name(encoderName.c_str());

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
      LOGE("Could not init codec context for '%s'\n", encoderName.c_str());
    }
  } else {
    LOGE("Could not open codec '%s'\n", encoderName.c_str());
  }

  return false;
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
