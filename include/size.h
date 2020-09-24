/*****************************************************************************
 * size.h
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
#ifndef SIZE_H
#define SIZE_H

namespace divomedia {
template <class Size_t>
class Size {
 public:
  Size() : mWidth(0), mHeight(0) {}
  Size(Size_t w, Size_t h) : mWidth(w), mHeight(h) {}
  Size(const Size &) = default;
  Size(Size &&) = default;
  Size &operator=(const Size &) = default;
  Size &operator=(Size &&) = default;
  bool operator==(const Size &other) const {
    return mWidth == other.mWidth && mHeight == other.mHeight;
  }
  bool operator!=(const Size &other) const {
    return mWidth != other.mWidth || mHeight != other.mHeight;
  }
  Size_t width() const { return mWidth; }
  Size_t height() const { return mHeight; }
  void setWidth(const Size_t &width) { mWidth = width; }
  void setHeight(const Size_t &height) { mHeight = height; }
  bool isNull() const { return mWidth == 0 && mHeight == 0; }

 private:
  Size_t mWidth;
  Size_t mHeight;
};
}  // namespace divomedia

#endif  // SIZE_H
