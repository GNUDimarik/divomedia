/*****************************************************************************
 * log.h
 *
 * Created: 20.09.2020 2020 by Dmitry Adzhiev <dmitry.adjiev@gmail.com>
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
#ifndef LOG_H
#define LOG_H

#include <config.h>

__BEGIN_DECLS
#include <libavutil/log.h>
__END_DECLS

#ifndef LOGD
#define LOGD(...) av_log(nullptr, AV_LOG_DEBUG, __VA_ARGS__)
#define LOGE(...) av_log(nullptr, AV_LOG_ERROR, __VA_ARGS__)
#endif

#endif  // LOG_H
