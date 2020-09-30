/*****************************************************************************
 * basicstream.h
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
#ifndef BASICSTREAM_H
#define BASICSTREAM_H

#include <config.h>
#include <utils/log.h>
#include <utils/utils.h>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

__BEGIN_DECLS
#include <libavformat/avformat.h>
__END_DECLS

namespace divomedia {

class BasicStream {
 public:
  enum OpenMode : std::uint8_t {
    kNone = 1L << 0,
    kIn = 1L << 1,
    kOut = 1L << 2
  };

  enum State : std::uint8_t { kOk = 0, kFail = 1, kEof };

  BasicStream() : mState(kOk), mOpenMode(kNone), mOpen(false) {}
  BasicStream(OpenMode mode) : mOpenMode(mode), mState(kFail), mOpen(false) {}
  bool isOpen() const { return mOpen; }
  State state() const { return mState; }
  bool isOk() const { return mState == kOk; }
  bool isFail() const { return mState == kFail; }
  void setOption(const std::string& key, const std::string& val) {
    mOptions[key] = val;
  }

  void close() { setOpen(false); }

  const std::string& getOption(
      const std::string& key, const std::string& defaultValue = std::string()) {
    const auto& searchResult = mOptions.find(key);
    return searchResult == mOptions.end() ? defaultValue : searchResult->second;
  }

  virtual BasicStream& operator>>(std::shared_ptr<AVFrame>&) { return *this; }
  virtual BasicStream& operator>>(std::shared_ptr<AVPacket>&) { return *this; }
  virtual BasicStream& operator<<(const std::shared_ptr<AVFrame>&) {
    return *this;
  }
  virtual BasicStream& operator<<(const std::shared_ptr<AVPacket>&) {
    return *this;
  }

 protected:
  void setState(State state) { mState = state; }
  virtual void setOpen(bool open) { mOpen = open; }
  std::shared_ptr<AVDictionary> optionsDictionary() const {
    return utils::Utils::optionsToDict(mOptions);
  }

 private:
  State mState;
  OpenMode mOpenMode;
  bool mOpen;
  std::unordered_map<std::string, std::string> mOptions;
};

}  // namespace divomedia

#endif  // BASICSTREAM_H
