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

#define FF_SUCCESSFUL(code) (code >= 0)
#define FF_FAILED(code) (code != 0)

#endif  // CONFIG_H
