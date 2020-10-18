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

#include <divomedia.h>

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
