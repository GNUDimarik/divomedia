/*****************************************************************************
 * pixelformat.h
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
#ifndef PIXELFORMAT_H
#define PIXELFORMAT_H

#include <features.h>

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
