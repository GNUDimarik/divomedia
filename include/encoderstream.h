/*****************************************************************************
 * encoderstream.h
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
#ifndef ENCODERSTREAM_H
#define ENCODERSTREAM_H

#include <basicstream.h>

namespace divomedia {

class EncoderStream : public BasicStream {
 public:
  EncoderStream(AVCodecID encoder = AV_CODEC_ID_NONE);
  bool open(AVCodecID encoder);
  AVCodecContext* avCodecContext() const;
  virtual EncoderStream& operator<<(
      const std::shared_ptr<AVFrame>& frame) override;
  virtual EncoderStream& operator>>(std::shared_ptr<AVPacket>& pkt) override;

 private:
  virtual EncoderStream& operator<<(
      const std::shared_ptr<AVPacket>& pkt) override {
    return *this;
  }
  virtual EncoderStream& operator>>(std::shared_ptr<AVFrame>& frame) override {
    return *this;
  }
  std::shared_ptr<AVCodecContext> mSpCodecContext;
};

}  // namespace divomedia

#endif  // ENCODERSTREAM_H
