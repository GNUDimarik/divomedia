/*****************************************************************************
 * ifilestream.cpp
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
      setState(kFail);
    }
  }

  if (isOk()) {
    AVFormatContext* ctx = avformat_alloc_context();

    if (ctx) {
      std::shared_ptr<AVDictionary> dict = optionsDictionary();
      AVDictionary* avDict = dict.get();
      int ret = avformat_open_input(&ctx, mFileName.c_str(),
                                    mSpInputFormat.get(), &avDict);

      if (FF_SUCCESSFUL(ret)) {
        // wrap AVFormatContext here since avformat_open_input calls
        // avformat_free_context if it fails and doesn't set pointer to nullptr
        // and then we crash in deleter
        mSpFormatCtx.reset(ctx, Deleter<AVFormatContext>::create());
        ret = avformat_find_stream_info(ctx, &avDict);

        if (FF_SUCCESSFUL(ret)) {
          // Success
          LOGD("Successfully opened '%s'\n", mFileName.c_str());
        } else {
          setState(kFail);
          LOGE("Could not find stream info for '%s' error: '%s'\n",
               mFileName.c_str(), Utils::avErrorToString(ret).c_str());
        }
      } else {
        setState(kFail);
        LOGE("Could not open '%s' error: '%s'\n", mFileName.c_str(),
             Utils::avErrorToString(ret).c_str());
      }
    } else {
      setState(kFail);
      LOGE("Could not intialize AVFormatContext\n");
    }
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
      LOGE("Input stream is not initialized");
    }
  } else {
    LOGE("Input stream is not open");
  }

  return 0;
}

AVStream* IFileStream::stream(unsigned int index) const {
  if (isOpen()) {
    if (mSpFormatCtx) {
      if (index >= 0 && index < mSpFormatCtx->nb_streams) {
        return mSpFormatCtx->streams[index];
      } else {
        LOGE("index %u out of range", index);
      }
    } else {
      LOGE("Input stream is not initialized");
    }
  } else {
    LOGE("Input stream is not open");
  }

  return nullptr;
}
