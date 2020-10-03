/*****************************************************************************
 * filter.h
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
#ifndef FILTER_H
#define FILTER_H

#include <utils/utils.h>

__BEGIN_DECLS
#include <libavfilter/avfilter.h>
__END_DECLS

namespace divomedia {
class Filter {
 public:
  Filter(AVFilterContext *ctx = nullptr);
  bool link(const Filter &filter, unsigned srcPad = 0, unsigned dstPad = 0);
  bool initialize(const std::string &parameters);
  bool isNull() const { return mpContext == nullptr; }

 protected:
  AVFilterContext *mpContext;
};
}  // namespace divomedia

#endif  // FILTER_H
