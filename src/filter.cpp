/*****************************************************************************
 * filter.cpp
 *
 * Created: 03.10.2020 2020 by Dmitry Adzhiev <dmitry.adjiev@gmail.com>
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
      LOGE("Destination filter isn't initialized");
    }
  } else {
    LOGE("Filter isn't initialized");
  }

  return false;
}

bool Filter::initialize(const std::string &parameters) {
  if (mpContext) {
    int ret = avfilter_init_str(mpContext, parameters.c_str());

    if (ret < 0) {
      LOGE("Could not initialize filter '%s' with string '%s' by error '%s'",
           mpContext->name, parameters.c_str(),
           Utils::avErrorToString(AVERROR(ret)).c_str());
    }

    return ret == 0;
  }

  return false;
}
