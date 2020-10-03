/*****************************************************************************
 * buffersink.h
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
#ifndef BUFFERSINK_H
#define BUFFERSINK_H

#include <filter.h>
#include <frame.h>

/// TODO: Implement more interface functions

namespace divomedia {

class BufferSink : public Filter {
 public:
  BufferSink(AVFilterContext *ctx = nullptr);
  bool getFrame(const Frame &frame) const;
};

}  // namespace divomedia
#endif  // BUFFERSINK_H
