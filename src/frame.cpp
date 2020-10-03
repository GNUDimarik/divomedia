/*****************************************************************************
 * frame.cpp
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
#include <frame.h>
#include <utils/deleter.h>

using namespace divomedia;
using namespace divomedia::utils;

Frame::Frame() : mSpFrame(Utils::createEmptyFrame()) {}

Frame::Frame(AVFrame* frame)
    : mSpFrame(std::shared_ptr<AVFrame>(frame, Deleter<AVFrame>::create())) {}

Frame::Frame(Frame&& other) noexcept { mSpFrame.swap(other.mSpFrame); }

AVFrame* Frame::avFrame() const { return mSpFrame.get(); }

void Frame::unref() const {
  if (mSpFrame) {
    av_frame_unref(mSpFrame.get());
  }
}

Frame& Frame::operator=(Frame&& frame) noexcept {
  if (mSpFrame != frame.mSpFrame) {
    mSpFrame.swap(frame.mSpFrame);
  }
  return *this;
}

Frame Frame::clone() {
  if (mSpFrame) {
    return Frame(av_frame_clone(mSpFrame.get()));
  }

  return Frame(nullptr);
}
