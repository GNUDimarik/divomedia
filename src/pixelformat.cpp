/*****************************************************************************
 * pixelformat.cpp
 *
 * Created: 11.09.2020 2020 by Dmitry Adzhiev <dmitry.adjiev@gmail.com>
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
