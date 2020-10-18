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

// TODO
typedef Size<int> Size_t;
}  // namespace divomedia

#endif  // SIZE_H
