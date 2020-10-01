/*****************************************************************************
 * decoderstream.h
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
#ifndef DECODERSTREAM_H
#define DECODERSTREAM_H

#include <basicstream.h>

__BEGIN_DECLS
#include <libavcodec/avcodec.h>
__END_DECLS

namespace divomedia {

class DecoderStream : public BasicStream {
 public:
  DecoderStream(AVStream* stream);

  bool open(AVCodecID decoder, bool openParser = true);
  virtual DecoderStream& operator<<(
      const std::shared_ptr<AVPacket>& pkt) override;
  virtual DecoderStream& operator>>(std::shared_ptr<AVFrame>& frame) override;

 private:
  virtual DecoderStream& operator<<(const std::shared_ptr<AVFrame>&) override {
    return *this;
  }

  virtual DecoderStream& operator>>(std::shared_ptr<AVPacket>&) override {
    return *this;
  }

  std::shared_ptr<AVCodecContext> mSpCodecContext;
  std::shared_ptr<AVCodecParserContext> mSpParserContext;
};

}  // namespace divomedia

#endif  // DECODERSTREAM_H
