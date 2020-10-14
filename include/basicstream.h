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

#ifndef BASICSTREAM_H
#define BASICSTREAM_H

#include <config.h>
#include <frame.h>
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
    kOut = 1L << 2,
    kInOut = kIn | kOut,
  };

  enum State : std::uint8_t { kOk = 0, kFail = 1, kEof };

  BasicStream() : mState(kOk), mOpenMode(kNone), mOpen(false) {}
  BasicStream(OpenMode mode) : mState(kFail), mOpenMode(mode), mOpen(false) {}
  bool isOpen() const { return mOpen; }
  State state() const { return mState; }
  bool isOk() const { return mState == kOk; }
  bool isFail() const { return mState == kFail; }
  void setOption(const std::string& key, const std::string& val) {
    mOptions[key] = val;
  }

  void close() { setOpen(false); }
  OpenMode openMode() const { return mOpenMode; }

  const std::string& getOption(
      const std::string& key, const std::string& defaultValue = std::string()) {
    const auto& searchResult = mOptions.find(key);
    return searchResult == mOptions.end() ? defaultValue : searchResult->second;
  }

  virtual BasicStream& operator>>(Frame&) { return *this; }
  virtual BasicStream& operator>>(std::shared_ptr<AVPacket>&) { return *this; }
  virtual BasicStream& operator<<(const Frame&) { return *this; }
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
