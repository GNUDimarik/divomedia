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

#ifndef DECODERSTREAM_H
#define DECODERSTREAM_H

#include <basicstream.h>

__BEGIN_DECLS
#include <libavcodec/avcodec.h>
__END_DECLS

namespace divomedia {

class DecoderStream : public BasicStream {
 public:
  DecoderStream(AVStream* stream = nullptr);
  AVCodecContext* avCodecContext() const;
  bool open(AVCodecID decoder, bool openParser = true);
  virtual DecoderStream& operator<<(
      const std::shared_ptr<AVPacket>& pkt) override;
  virtual DecoderStream& operator>>(Frame& frame) override;

 private:
  virtual DecoderStream& operator<<(const Frame&) override { return *this; }

  virtual DecoderStream& operator>>(std::shared_ptr<AVPacket>&) override {
    return *this;
  }

  std::shared_ptr<AVCodecContext> mSpCodecContext;
  std::shared_ptr<AVCodecParserContext> mSpParserContext;
};  // namespace divomedia

}  // namespace divomedia

#endif  // DECODERSTREAM_H
