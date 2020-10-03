/*****************************************************************************
 * filterstream.h
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
#ifndef FILTERSTREAM_H
#define FILTERSTREAM_H

#include <basicstream.h>
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
               Kind kind = kNone);
  virtual FilterStream& operator>>(std::shared_ptr<AVFrame>& frame);
  virtual FilterStream& operator<<(const std::shared_ptr<AVFrame>& frame);
  Filter createFilter(const std::string& filterName,
                      const std::string& objectName = std::string()) const;
  bool validate() const;
  bool initializeFromDescription(const std::string& description, Kind kind);

 private:
  virtual FilterStream& operator>>(std::shared_ptr<AVPacket>&) { return *this; }
  virtual FilterStream& operator<<(const std::shared_ptr<AVPacket>&) {
    return *this;
  }

  std::shared_ptr<AVFilterGraph> mSpFilterGraph;
};

}  // namespace divomedia

#endif  // FILTERSTREAM_H
