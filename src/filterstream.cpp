/*****************************************************************************
 * filterstream.cpp
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
#include <filterstream.h>
#include <utils/log.h>
#include <utils/utils.h>

using namespace divomedia;
using namespace divomedia::utils;

FilterStream::FilterStream(const std::string& description, Kind kind)
    : BasicStream(kInOut) {
  if (description.empty()) {
    mSpFilterGraph = Utils::createFilterGraph();
  } else {
    initializeFromDescription(description, kind);
  }
}

FilterStream& FilterStream::operator>>(std::shared_ptr<AVFrame>& frame) {
  return *this;
}

FilterStream& FilterStream::operator<<(const std::shared_ptr<AVFrame>& frame) {
  return *this;
}

Filter FilterStream::createFilter(const std::string& filterName,
                                  const std::string& objectName) const {
  AVFilterContext* filterContext = nullptr;
  const AVFilter* avFilter = avfilter_get_by_name(filterName.c_str());

  if (avFilter) {
    filterContext = avfilter_graph_alloc_filter(mSpFilterGraph.get(), avFilter,
                                                objectName.c_str());

    if (filterContext) {
      return Filter(filterContext);
    } else {
      LOGE("Could not create filter '%s' with name '%s'", filterName.c_str(),
           objectName.c_str());
    }
  } else {
    LOGE("Could not find filter '%s'", filterName.c_str());
  }

  return Filter();
}

bool FilterStream::validate() const {
  int ret = avfilter_graph_config(mSpFilterGraph.get(), nullptr);

  if (ret < 0) {
    LOGE("Failed graph validation. Message is '%s'",
         Utils::avErrorToString(AVERROR(ret)).c_str());
  }

  return ret >= 0;
}

bool FilterStream::initializeFromDescription(const std::string& description,
                                             Kind kind) {}
