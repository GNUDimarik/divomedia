/*****************************************************************************
 * buffersource.cpp
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
#include <buffersource.h>
#include <utils/log.h>
#include <utils/utils.h>

__BEGIN_DECLS
#include <libavfilter/buffersrc.h>
__END_DECLS

using namespace divomedia;
using namespace divomedia::utils;

BufferSource::BufferSource(AVFilterContext *ctx) : Filter(ctx) {}

bool BufferSource::add(const std::shared_ptr<AVFrame> &frame, int flags) {
  if (!isNull()) {
    int ret = -1;

    if (flags > 0) {
      ret = av_buffersrc_add_frame_flags(mpContext, frame.get(), flags);
    } else {
      ret = av_buffersrc_add_frame(mpContext, frame.get());
    }

    if (ret < 0) {
      LOGE("Failed to add frame '%s'",
           Utils::avErrorToString(AVERROR(ret)).c_str());
    }

    return ret >= 0;
  } else {
    LOGE("BufferSource: isn't initialized");
  }

  return false;
}

bool BufferSource::write(const std::shared_ptr<AVFrame> &frame) {
  if (!isNull()) {
    int ret = av_buffersrc_write_frame(mpContext, frame.get());

    if (ret < 0) {
      LOGE("Failed to write frame '%s'",
           Utils::avErrorToString(AVERROR(ret)).c_str());
    }

    return ret >= 0;
  }

  return false;
}
