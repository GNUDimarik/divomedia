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

#include <buffersource.h>
#include <utils/log.h>
#include <utils/utils.h>

__BEGIN_DECLS
#include <libavfilter/buffersrc.h>
__END_DECLS

using namespace divomedia;
using namespace divomedia::utils;

BufferSource::BufferSource(AVFilterContext *ctx) : Filter(ctx) {}

bool BufferSource::add(const Frame &frame, int flags) {
  if (!isNull()) {
    int ret = -1;

    if (flags > 0) {
      ret = av_buffersrc_add_frame_flags(mpContext, frame.avFrame(), flags);
    } else {
      ret = av_buffersrc_add_frame(mpContext, frame.avFrame());
    }

    if (ret < 0) {
      LOGE("BufferSource: Failed to add frame '%s'\n",
           Utils::avErrorToString(AVERROR(ret)).c_str());
    }

    return ret >= 0;
  } else {
    LOGE("BufferSource: isn't initialized\n");
  }

  return false;
}

bool BufferSource::write(const Frame &frame) {
  if (!isNull()) {
    int ret = av_buffersrc_write_frame(mpContext, frame.avFrame());

    if (ret < 0) {
      LOGE("BufferSource: Failed to write frame '%s'\n",
           Utils::avErrorToString(AVERROR(ret)).c_str());
    }

    return ret >= 0;
  }

  return false;
}
