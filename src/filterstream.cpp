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
  mSpFilterGraph = Utils::createFilterGraph();

  if (description.empty()) {
    initializeSinkAndSource(kind);
  } else {
    initializeFromDescription(description, kind);
  }
}

void FilterStream::createBufferSource(const std::string& bufferSource,
                                      const std::string& objectName) {
  if (!mSpBufferSource) {
    mSpBufferSource.reset(new BufferSource(
        createFilter(bufferSource, objectName).avFilterContext()));
  }
}

void FilterStream::createBufferSink(const std::string& bufferSink,
                                    const std::string& objectName) {
  if (!mSpBufferSink) {
    mSpBufferSink.reset(
        new BufferSink(createFilter(bufferSink, objectName).avFilterContext()));
  }
}

void FilterStream::initializeSinkAndSource(Kind kind) {
  switch (kind) {
    case kAudio:
      createBufferSource("abuffersrc");
      createBufferSink("abuffersink");
      break;

    case kVideo:
      createBufferSource("buffersrc");
      createBufferSink("buffersink");
      break;

    default:
      break;
  }
}

BufferSource* FilterStream::source() const { return mSpBufferSource.get(); }

BufferSink* FilterStream::sink() const { return mSpBufferSink.get(); }

FilterStream& FilterStream::operator>>(Frame& frame) {
  setState(kFail);

  if (mSpBufferSink) {
    mSpBufferSink->getFrame(frame) ? setState(kOk) : setState(kFail);
  }

  return *this;
}

FilterStream& FilterStream::operator<<(const Frame& frame) {
  setState(kFail);

  if (mSpBufferSource) {
    mSpBufferSource->write(frame) ? setState(kOk) : setState(kFail);
  }

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

bool FilterStream::validate() {
  int ret = avfilter_graph_config(mSpFilterGraph.get(), nullptr);

  if (ret >= 0) {
    setOpen(false);
    setState(kOk);
  } else {
    LOGE("Failed graph validation. Message is '%s'",
         Utils::avErrorToString(AVERROR(ret)).c_str());
  }

  return ret >= 0;
}

bool FilterStream::initializeFromDescription(const std::string& description,
                                             Kind kind) {
  initializeSinkAndSource(kind);

  if (!description.empty()) {
    AVFilterInOut* outputs = avfilter_inout_alloc();
    AVFilterInOut* inputs = avfilter_inout_alloc();
    outputs->name = av_strdup("in");
    outputs->filter_ctx = mSpBufferSource->avFilterContext();
    outputs->pad_idx = 0;
    outputs->next = nullptr;

    inputs->name = av_strdup("out");
    inputs->filter_ctx = mSpBufferSink->avFilterContext();
    inputs->pad_idx = 0;
    inputs->next = nullptr;

    int ret = avfilter_graph_parse_ptr(
        mSpFilterGraph.get(), description.c_str(), &inputs, &outputs, nullptr);

    if (ret < 0) {
      LOGE("Could not initialize graph from description '%s' by error '%s'",
           description.c_str(), Utils::avErrorToString(AVERROR(ret)).c_str());
    }

    avfilter_inout_free(&inputs);
    avfilter_inout_free(&outputs);

    return ret >= 0;
  }

  return false;
}
