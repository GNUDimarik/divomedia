/*****************************************************************************
 * main.cpp
 *
 * Created: 19.09.2020 2020 by Dmitry Adzhiev <dmitry.adjiev@gmail.com>
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

#include <config.h>

__BEGIN_DECLS
#ifndef DIVO_MEDIA_NO_AVDEVICE
#include <libavdevice/avdevice.h>
#endif
#include <libavutil/log.h>
__END_DECLS

namespace divomedia {

#if defined(ANDROID) || defined(__ANDROID__)
#include <cstdarg>
#include <cstdio>
#ifndef DIVO_MEDIA_AOSP
#include <android/log.h>
#else
#include <utils/Log.h>
#endif

#define BUFFER_SIZE 2048
#define LOG_TAG "ffmpeg"

static void log_callback(void *, int, const char *fmt, va_list ap) {
  char buffer[BUFFER_SIZE];
  vsprintf(buffer, fmt, ap);
  ALOGD("%s", buffer);
}

#endif

void init() {
#ifndef DIVO_MEDIA_NO_AVDEVICE
  avdevice_register_all();
#endif

  av_log_set_level(AV_LOG_DEBUG);

#if defined(ANDROID) || defined(__ANDROID__)
  av_log_set_callback(log_callback);
#endif
}

}  // namespace divomedia
