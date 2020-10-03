/*****************************************************************************
 * buffersink.cpp
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
      LOGE("BufferSink: failed to get frame '%s'",
           Utils::avErrorToString(AVERROR(ret)).c_str());
    }

    return ret >= 0;
  }

  return false;
}
