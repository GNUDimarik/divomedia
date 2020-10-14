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

#include <filter.h>
#include <utils/log.h>
#include <utils/utils.h>

#define BUFFER_SIZE 1024

using namespace divomedia;
using namespace divomedia::utils;

Filter::Filter(AVFilterContext *ctx) : mpContext(ctx) {}

bool Filter::link(const Filter &filter, unsigned srcPad, unsigned dstPad) {
  if (mpContext) {
    if (filter.mpContext) {
      return avfilter_link(mpContext, srcPad, filter.mpContext, dstPad) == 0;
    } else {
      LOGE("Destination filter isn't initialized\n");
    }
  } else {
    LOGE("Filter isn't initialized\n");
  }

  return false;
}

bool Filter::initialize(const std::string &parameters) {
  if (mpContext) {
    int ret = avfilter_init_str(mpContext, parameters.c_str());

    if (ret < 0) {
      LOGE("Could not initialize filter '%s' with string '%s' by error '%s'\n",
           mpContext->name, parameters.c_str(),
           Utils::avErrorToString(AVERROR(ret)).c_str());
    }

    return ret == 0;
  }

  return false;
}
