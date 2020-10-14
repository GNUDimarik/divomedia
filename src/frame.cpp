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

#include <frame.h>
#include <utils/deleter.h>

using namespace divomedia;
using namespace divomedia::utils;

Frame::Frame() : mSpFrame(Utils::createEmptyFrame()) {}

Frame::Frame(std::uint8_t* data, std::size_t len) {
  // av_frame_get_buffer()
}

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
