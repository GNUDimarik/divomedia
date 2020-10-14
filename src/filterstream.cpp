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

#include <filterstream.h>
#include <utils/log.h>
#include <utils/utils.h>

__BEGIN_DECLS
#include <libavutil/opt.h>
__END_DECLS

using namespace divomedia;
using namespace divomedia::utils;

FilterStream::FilterStream(const std::string& description,
                           const std::string& srcParameters, Kind kind)
    : BasicStream(kInOut) {
  mSpFilterGraph = Utils::createFilterGraph();

  if (description.empty()) {
    std::string sourceName = kind == kVideo ? "buffer" : "abuffer";
    std::string sinkName = kind == kVideo ? "buffersink" : "abuffersink";
    createBufferSource(sourceName, srcParameters);
    createBufferSink(sinkName);
  } else {
    initializeFromDescription(description, srcParameters, kind);
  }
}

void FilterStream::createBufferSource(const std::string& bufferSource,
                                      const std::string& objectName,
                                      const std::string& parameters) {
  mSpBufferSource.reset(new BufferSource(
      createFilter(bufferSource, objectName, parameters).avFilterContext()));
}

void FilterStream::createBufferSink(const std::string& bufferSink,
                                    const std::string& objectName,
                                    const std::string& parameters) {
  mSpBufferSink.reset(new BufferSink(
      createFilter(bufferSink, objectName, parameters).avFilterContext()));
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
  frame.avFrame()->pts = frame.avFrame()->best_effort_timestamp;

  if (mSpBufferSource) {
    mSpBufferSource->add(frame) ? setState(kOk) : setState(kFail);
  }

  return *this;
}

Filter FilterStream::createFilter(const std::string& filterName,
                                  const std::string& objectName,
                                  const std::string& parameters) const {
  AVFilterContext* filterContext = nullptr;
  const AVFilter* avFilter = avfilter_get_by_name(filterName.c_str());

  if (avFilter) {
    int ret = avfilter_graph_create_filter(
        &filterContext, avFilter, objectName.c_str(), parameters.c_str(),
        nullptr, mSpFilterGraph.get());

    if (ret >= 0) {
      return Filter(filterContext);
    } else {
      LOGE("Could not create filter '%s' with name '%s' by error '%s'\n",
           filterName.c_str(), objectName.c_str(),
           Utils::avErrorToString(AVERROR(ret)).c_str());
    }
  } else {
    LOGE("Could not find filter '%s'\n", filterName.c_str());
  }

  return Filter();
}

bool FilterStream::validate() {
  int ret = avfilter_graph_config(mSpFilterGraph.get(), nullptr);

  if (ret >= 0) {
    setOpen(false);
    setState(kOk);
  } else {
    LOGE("Failed graph validation. Message is '%s'\n",
         Utils::avErrorToString(AVERROR(ret)).c_str());
  }

  return ret >= 0;
}

bool FilterStream::initializeFromDescription(const std::string& description,
                                             const std::string& srcParameters,
                                             Kind kind) {
  std::string sourceName = kind == kVideo ? "buffer" : "abuffer";
  std::string sinkName = kind == kVideo ? "buffersink" : "abuffersink";

  if (!description.empty()) {
    createBufferSource(sourceName, "in", srcParameters);
    createBufferSink(sinkName, "out");
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
      LOGE("Could not initialize graph from description '%s' by error '%s'\n",
           description.c_str(), Utils::avErrorToString(AVERROR(ret)).c_str());
    }

    avfilter_inout_free(&inputs);
    avfilter_inout_free(&outputs);

    return ret >= 0;
  }

  return false;
}
