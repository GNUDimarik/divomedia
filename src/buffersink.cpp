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

#include <buffersink.h>
#include <utils/log.h>
#include <utils/utils.h>

__BEGIN_DECLS
#include <libavfilter/buffersink.h>
__END_DECLS

using namespace divomedia;
using namespace divomedia::utils;

BufferSink::BufferSink(AVFilterContext *ctx) : Filter(ctx) {}

bool BufferSink::getFrame(const Frame &frame) const {
  if (!isNull()) {
    int ret = av_buffersink_get_frame(mpContext, frame.avFrame());

    if (ret < 0) {
      LOGE("BufferSink: failed to get frame '%s'\n",
           Utils::avErrorToString(AVERROR(ret)).c_str());
    }

    return ret >= 0;
  }

  return false;
}
