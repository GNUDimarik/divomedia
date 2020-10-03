/*****************************************************************************
 * buffersource.h
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
#ifndef BUFFERSOURCE_H
#define BUFFERSOURCE_H

#include <filter.h>

__BEGIN_DECLS
#include <libavformat/avformat.h>
__END_DECLS

#include <memory>

namespace divomedia {

class BufferSource : public Filter {
 public:
  BufferSource(AVFilterContext *ctx);
  bool add(const std::shared_ptr<AVFrame> &frame, int flags = 0);
  bool write(const std::shared_ptr<AVFrame> &frame);
};

}  // namespace divomedia

#endif  // BUFFERSOURCE_H
