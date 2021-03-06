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

#include "pixelformat.h"

#include <algorithm>

using namespace divomedia;

PixelFormat::PixelFormat(AVPixelFormat pixelFormat)
    : mPixelFormat(pixelFormat) {}

std::string PixelFormat::toString() const {
  return av_get_pix_fmt_name(mPixelFormat);
}

bool PixelFormat::isNone() const { return mPixelFormat == AV_PIX_FMT_NONE; }

AVPixelFormat PixelFormat::toAvPixelFormat() const { return mPixelFormat; }

PixelFormat &PixelFormat::operator=(AVPixelFormat fmt) {
  mPixelFormat = fmt;
  return *this;
}

PixelFormat &PixelFormat::operator=(const PixelFormat &fmt) {
  mPixelFormat = fmt.mPixelFormat;
  return *this;
}

bool PixelFormat::operator==(const AVPixelFormat &fmt) const {
  return mPixelFormat == fmt;
}

bool PixelFormat::operator!=(const AVPixelFormat &fmt) const {
  return mPixelFormat != fmt;
}

bool PixelFormat::operator==(const PixelFormat &fmt) const {
  return mPixelFormat == fmt.mPixelFormat;
}

bool PixelFormat::operator!=(PixelFormat &fmt) const {
  return mPixelFormat != fmt.mPixelFormat;
}
