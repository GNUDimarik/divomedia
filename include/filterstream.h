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

#ifndef FILTERSTREAM_H
#define FILTERSTREAM_H

#include <basicstream.h>
#include <buffersink.h>
#include <buffersource.h>
#include <filter.h>

__BEGIN_DECLS
#include <libavfilter/avfilter.h>
__END_DECLS

#include <memory>

namespace divomedia {

class FilterStream : BasicStream {
 public:
  enum Kind { kNone = 0, kAudio = 1, kVideo = 2 };

  FilterStream(const std::string& description = std::string(),
               const std::string& srcParameters = std::string(),
               Kind kind = kNone);
  void createBufferSource(const std::string& bufferSource,
                          const std::string& objectName = std::string(),
                          const std::string& parameters = std::string());
  void createBufferSink(const std::string& bufferSink,
                        const std::string& objectName = std::string(),
                        const std::string& parameters = std::string());
  BufferSource* source() const;
  BufferSink* sink() const;
  virtual FilterStream& operator>>(Frame& frame) override;
  virtual FilterStream& operator<<(const Frame& frame) override;
  Filter createFilter(const std::string& filterName,
                      const std::string& objectName = std::string(),
                      const std::string& parameters = std::string()) const;
  bool validate();
  bool initializeFromDescription(const std::string& description,
                                 const std::string& srcParameters, Kind kind);

 private:
  virtual FilterStream& operator>>(std::shared_ptr<AVPacket>&) override {
    return *this;
  }
  virtual FilterStream& operator<<(const std::shared_ptr<AVPacket>&) override {
    return *this;
  }

  std::shared_ptr<AVFilterGraph> mSpFilterGraph;
  std::unique_ptr<BufferSource> mSpBufferSource;
  std::unique_ptr<BufferSink> mSpBufferSink;
};

}  // namespace divomedia

#endif  // FILTERSTREAM_H
