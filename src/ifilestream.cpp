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

#include "ifilestream.h"
#include <utils/deleter.h>
#include <utils/log.h>
#include <utils/utils.h>

__BEGIN_DECLS
#include <libavformat/avformat.h>
__END_DECLS

using namespace divomedia;
using namespace divomedia::utils;

IFileStream::IFileStream(const std::string& fileName, OpenMode mode,
                         const std::string& inputFormat)
    : BasicStream(mode), mFileName(fileName), mInputFormat(inputFormat) {
  if (!mInputFormat.empty()) {
    mSpInputFormat.reset(av_find_input_format(mInputFormat.c_str()),
                         Deleter<AVInputFormat>::create());

    if (!mSpInputFormat) {
      LOGE("Could not find input format '%s'", mInputFormat.c_str());
    }
  }

  AVFormatContext* ctx = avformat_alloc_context();

  if (ctx) {
    std::shared_ptr<AVDictionary> dict = optionsDictionary();
    AVDictionary* avDict = dict.get();
    int ret = avformat_open_input(&ctx, mFileName.c_str(), mSpInputFormat.get(),
                                  &avDict);

    if (FF_SUCCESSFUL(ret)) {
      // wrap AVFormatContext here since avformat_open_input calls
      // avformat_free_context if it fails and doesn't set pointer to nullptr
      // and then we crash in deleter
      mSpFormatCtx.reset(ctx, Deleter<AVFormatContext>::create());
      ret = avformat_find_stream_info(ctx, &avDict);

      if (FF_SUCCESSFUL(ret)) {
        // Success
        setState(kOk);
        setOpen(true);
        LOGD("Successfully opened '%s'\n", mFileName.c_str());
      } else {
        LOGE("Could not find stream info for '%s' error: '%s'\n",
             mFileName.c_str(), Utils::avErrorToString(ret).c_str());
      }
    } else {
      LOGE("Could not open '%s' error: '%s'\n", mFileName.c_str(),
           Utils::avErrorToString(ret).c_str());
    }
  } else {
    LOGE("Could not intialize AVFormatContext\n");
  }
}

IFileStream& IFileStream::operator>>(std::shared_ptr<AVPacket>& packet) {
  if (isOpen()) {
    int ret = av_read_frame(mSpFormatCtx.get(), packet.get());

    if (ret < 0) {
      if (ret == AVERROR_EOF) {
        setState(kEof);
      } else {
        setState(kFail);
      }
    }
  }
  return *this;
}

unsigned int IFileStream::streamsNumber() const {
  if (isOpen()) {
    if (mSpFormatCtx) {
      return mSpFormatCtx->nb_streams;
    } else {
      LOGE("Input stream is not initialized\n");
    }
  } else {
    LOGE("Input stream is not open\n");
  }

  return 0;
}

AVStream* IFileStream::stream(unsigned int index) const {
  if (isOpen()) {
    if (mSpFormatCtx) {
      if (index >= 0 && index < mSpFormatCtx->nb_streams) {
        return mSpFormatCtx->streams[index];
      } else {
        LOGE("index %u out of range\n", index);
      }
    } else {
      LOGE("Input stream is not initialized\n");
    }
  } else {
    LOGE("Input stream is not open\n");
  }

  return nullptr;
}
