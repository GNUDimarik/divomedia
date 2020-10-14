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

#ifndef IFILESTREAM_H
#define IFILESTREAM_H

#include <basicstream.h>
#include <config.h>
#include <memory>

__BEGIN_DECLS
#include <libavformat/avformat.h>
__END_DECLS

namespace divomedia {

class IFileStream : public BasicStream {
 public:
  IFileStream(const std::string& fileName, OpenMode mode,
              const std::string& inputFormat = std::string());
  virtual IFileStream& operator>>(std::shared_ptr<AVPacket>& packet) override;
  unsigned int streamsNumber() const;
  AVStream* stream(unsigned int index) const;

 private:
  IFileStream& operator>>(Frame& frame) override { return *this; }

  virtual IFileStream& operator<<(const Frame& frame) override { return *this; }
  virtual IFileStream& operator<<(
      const std::shared_ptr<AVPacket>& packet) override {
    return *this;
  }

  std::string mFileName;
  std::string mInputFormat;
  std::shared_ptr<AVFormatContext> mSpFormatCtx;
  std::shared_ptr<AVInputFormat> mSpInputFormat;
};

}  // namespace divomedia

#endif  // IFILESTREAM_H
