/*****************************************************************************
 * frame.h
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
#ifndef FRAME_H
#define FRAME_H

#include <utils/utils.h>

__BEGIN_DECLS
#include <libavutil/frame.h>
__END_DECLS

#include <memory>

namespace divomedia {

class Frame {
 public:
  Frame();
  Frame(AVFrame* frame);
  Frame(const Frame&) = delete;
  Frame(Frame&& other) noexcept;
  AVFrame* avFrame() const;
  void unref() const;
  Frame operator=(const Frame& frame) = delete;
  Frame& operator=(Frame&& frame) noexcept;
  Frame clone();

 private:
  std::shared_ptr<AVFrame> mSpFrame;
};

}  // namespace divomedia

#endif  // FRAME_H
