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

#ifndef ENCODERSTREAM_H
#define ENCODERSTREAM_H

#include <basicstream.h>

namespace divomedia {

class EncoderStream : public BasicStream {
 public:
  EncoderStream(AVCodecID encoder = AV_CODEC_ID_NONE);
  AVCodecContext* avCodecContext() const;
  bool open(AVCodecID encoder);
  bool open(const std::string& encoderName);
  virtual EncoderStream& operator<<(const Frame& frame) override;
  virtual EncoderStream& operator>>(std::shared_ptr<AVPacket>& pkt) override;

 private:
  virtual EncoderStream& operator<<(
      const std::shared_ptr<AVPacket>& pkt) override {
    return *this;
  }
  virtual EncoderStream& operator>>(Frame& frame) override { return *this; }
  std::shared_ptr<AVCodecContext> mSpCodecContext;
};

}  // namespace divomedia

#endif  // ENCODERSTREAM_H
