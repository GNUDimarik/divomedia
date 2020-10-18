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

#include <config.h>
#include <image.h>
#include <utils/log.h>
#include <utils/utils.h>
#include <algorithm>

__BEGIN_DECLS
#include <libavutil/imgutils.h>
__END_DECLS

using namespace divomedia;

Image Image::createFromData(const Size_t &size, PixelFormat pixelFormat,
                            const uint8_t *data) {
  Image image = create(size, pixelFormat);

  if (!pixelFormat.isNone()) {
    int bufferSize = av_image_get_buffer_size(pixelFormat.toAvPixelFormat(),
                                              size.width(), size.height(), 1);

    if (bufferSize > 0) {
      image.mSize = size;

      int ret = av_image_fill_arrays(image.mpPointers, image.maLineSizes, data,
                                     pixelFormat.toAvPixelFormat(),
                                     size.width(), size.height(), 1);

      if (ret < 0) {
        LOGE("Could not create image from data. Error '%s'\n",
             utils::Utils::avErrorToString(ret).c_str());
      }
    }
  }

  return image;
}

Image Image::create(const Size_t &size, PixelFormat pixelFormat) {
  Image image;
  image.mPixelFormat = pixelFormat;

  int ret = av_image_alloc(image.mpPointers, image.maLineSizes, size.width(),
                           size.height(), pixelFormat.toAvPixelFormat(), 1);

  if (ret < 0) {
    image.mPixelFormat = PixelFormat();
    LOGE("Could not allocate image. Error '%s'\n",
         utils::Utils::avErrorToString(ret).c_str());
  }

  return image;
}

Image::Image() {
  for (std::size_t i = 0; i < ARRAY_SIZE(mpPointers); i++) {
    mpPointers[i] = nullptr;
  }

  for (std::size_t i = 0; i < ARRAY_SIZE(maLineSizes); i++) {
    maLineSizes[i] = 0;
  }
}

Image::Image(const std::uint8_t *data, std::size_t size) {}

Image::Image(Image &&tmp) noexcept {
  std::swap(mpPointers, tmp.mpPointers);
  std::swap(maLineSizes, tmp.maLineSizes);
  std::swap(mPixelFormat, tmp.mPixelFormat);
  std::swap(mSize, tmp.mSize);
}

Image::~Image() { release(); }

void Image::release() {
  if (!isEmpty()) {
    av_freep(mpPointers);
    mSize.setHeight(0);
    mSize.setWidth(0);
  }
}

bool Image::isEmpty() { return mpPointers[0] == nullptr; }

Image Image::scale(const Size_t &size, int algorithm) {
  return swsScale(size, mPixelFormat, algorithm);
}

Image Image::toPixelFormat(PixelFormat pixelFormat, int algorithm) {
  return swsScale(mSize, pixelFormat, algorithm);
}

Image Image::swsScale(const Size_t &size, const PixelFormat &pixelFormat,
                      int algorithm) {
  SwsContext *sws_ctx = sws_getContext(
      mSize.width(), mSize.height(), mPixelFormat.toAvPixelFormat(),
      size.width(), size.height(), pixelFormat.toAvPixelFormat(), algorithm,
      nullptr, nullptr, nullptr);

  Image img = create(size, pixelFormat);
  int ret = sws_scale(sws_ctx, mpPointers, maLineSizes, 0, mSize.height(),
                      img.mpPointers, img.maLineSizes);
  if (ret <= 0) {
    LOGE("Could not scale image. Error '%s'\n",
         utils::Utils::avErrorToString(ret).c_str());
  }

  sws_freeContext(sws_ctx);
  return img;
}
