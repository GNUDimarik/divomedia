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

#ifndef PIXELFORMAT_H
#define PIXELFORMAT_H

#if __has_include(<features.h>)
#include <features.h>
#else
#include <config.h>
#endif

__BEGIN_DECLS
#include <libavutil/pixdesc.h>
#include <libavutil/pixfmt.h>
__END_DECLS

#include <string>

namespace divomedia {

class PixelFormat {
 public:
  PixelFormat(AVPixelFormat pixelFormat = AV_PIX_FMT_NONE);
  PixelFormat(const PixelFormat &) = default;
  PixelFormat(PixelFormat &&) = default;
  std::string toString() const;
  bool isNone() const;
  AVPixelFormat toAvPixelFormat() const;
  PixelFormat &operator=(AVPixelFormat fmt);
  PixelFormat &operator=(const PixelFormat &fmt);
  bool operator==(const AVPixelFormat &fmt) const;
  bool operator!=(const AVPixelFormat &fmt) const;
  bool operator==(const PixelFormat &fmt) const;
  bool operator!=(PixelFormat &fmt) const;

 private:
  AVPixelFormat mPixelFormat;
};

}  // namespace divomedia

#endif  // PIXELFORMAT_H
