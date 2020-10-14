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

#ifndef FILTER_H
#define FILTER_H

#include <utils/utils.h>

__BEGIN_DECLS
#include <libavfilter/avfilter.h>
__END_DECLS

namespace divomedia {
class Filter {
 public:
  Filter(AVFilterContext *ctx = nullptr);
  bool link(const Filter &filter, unsigned srcPad = 0, unsigned dstPad = 0);
  bool initialize(const std::string &parameters);
  bool isNull() const { return mpContext == nullptr; }
  AVFilterContext *avFilterContext() const { return mpContext; }
  void invalidate() { mpContext = nullptr; }

 protected:
  AVFilterContext *mpContext;
};
}  // namespace divomedia

#endif  // FILTER_H
