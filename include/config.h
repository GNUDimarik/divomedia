/*****************************************************************************
 * config.h
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
#ifndef CONFIG_H
#define CONFIG_H

#if defined(__MINGW32__) || defined(__MINGW64__)
/* MINGW compiler */
#define DIVO_MEDIA_COMPILER_MINGW
#elif defined(_MSC_VER)
/* MSVC compiler */
#define DIVO_MEDIA_COMPILER_MSVC
#elif defined(__INTEL_COMPILER)
/* INTEL compiler */
#elif defined(__GNUC__)
#include <features.h>
/* GNU C compiler */
#define DIVO_MEDIA_COMPILER_GCC
#endif

#if defined(_WIN32) || defined(_WIN64)
#define DIVO_MEDIA_OS_WINDOWS
#endif

#if defined(__linux__)
#define DIVO_MEDIA_OS_LINUX
#endif

#if defined(__ANDROID__)
#define DIVO_MEDIA_OS_ANDROID
#endif

#ifndef __BEGIN_DECLS
#define __BEGIN_DECLS extern "C" {
#endif

#ifndef __END_DECLS
#define __END_DECLS }
#endif

#define FF_SUCCESSFUL(code) (code == 0)
#define FF_FAILED(code) (code != 0)

#endif  // CONFIG_H
