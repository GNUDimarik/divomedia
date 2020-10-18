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
#ifndef IMAGE_H
#define IMAGE_H

#include <pixelformat.h>
#include <size.h>

__BEGIN_DECLS
#include <libswscale/swscale.h>
__END_DECLS

namespace divomedia {

class Image {
 public:
  static Image createFromData(const Size_t &size, PixelFormat pixelFormat,
                              const std::uint8_t *data = nullptr);
  static Image create(const Size_t &size, PixelFormat pixelFormat);

  Image();
  Image(const Image &) = delete;
  Image(Image &&tmp) noexcept;
  Image(const std::uint8_t *data, std::size_t size);
  virtual ~Image();
  void release();
  bool isEmpty();
  /// TODO:
  Image scale(const Size_t &size, int algorithm = SWS_BILINEAR);
  Image toPixelFormat(PixelFormat pixelFormat, int algorithm = SWS_BILINEAR);

 private:
  Image swsScale(const Size_t &size, const PixelFormat &pixelFormat,
                 int algorithm = SWS_BILINEAR);

  std::uint8_t *mpPointers[4];
  int maLineSizes[4];
  PixelFormat mPixelFormat;
  Size_t mSize;
};

}  // namespace divomedia

#endif  // IMAGE_H
