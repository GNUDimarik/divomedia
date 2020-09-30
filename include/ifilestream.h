/*****************************************************************************
 * ifilestream.h
 *
 * Created: 20.09.2020 2020 by Dmitry Adzhiev <dmitry.adjiev@gmail.com>
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
#ifndef IFILESTREAM_H
#define IFILESTREAM_H

#include <basicstream.h>
#include <config.h>
#include <memory>

__BEGIN_DECLS
#include <libavformat/avformat.h>
__END_DECLS

namespace divomedia {

class IFileStream : public BasicStream {
 public:
  IFileStream(const std::string& fileName, OpenMode mode,
              const std::string& inputFormat = std::string());
  virtual IFileStream& operator>>(std::shared_ptr<AVPacket>& packet) override;
  unsigned int streamsNumber() const;
  AVStream* stream(unsigned int index) const;

 private:
  IFileStream& operator>>(std::shared_ptr<AVFrame>& frame) override {
    return *this;
  }

  virtual IFileStream& operator<<(
      const std::shared_ptr<AVFrame>& frame) override {
    return *this;
  }
  virtual IFileStream& operator<<(
      const std::shared_ptr<AVPacket>& packet) override {
    return *this;
  }

  std::string mFileName;
  std::string mInputFormat;
  std::shared_ptr<AVFormatContext> mSpFormatCtx;
  std::shared_ptr<AVInputFormat> mSpInputFormat;
};

}  // namespace divomedia

#endif  // IFILESTREAM_H
