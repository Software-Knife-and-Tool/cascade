/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  GyreEnv.h: gyre environment class
 **
 **/
#ifndef _GYREUI_SRC_UI_GYREENV_H_
#define _GYREUI_SRC_UI_GYREENV_H_

#include <QString>

#include "libmu/libmu.h"

namespace gyreui {

using libmu::platform::Platform;

class GyreEnv {
 public:
  QString version() { return QString(libmu::api::version()); }

  QString rep(QString form) {
    auto rval =
        libmu::api::eval(env, libmu::api::read_string(env, form.toStdString()));

    auto str = std::string(libmu::api::print_cstr(env, rval, true));
    return QString::fromStdString(Platform::GetStdString(stdout) + str);
  }

  QString withException(std::function<void()> fn) {
    libmu::api::withException(env, [fn](void*) { (void)fn(); });
    return QString::fromStdString(Platform::GetStdString(stderr));
  }

  GyreEnv() : platform(new Platform()) {
    stdout = Platform::OpenOutputString("");
    stderr = Platform::OpenOutputString("");

    env = libmu::api::env(platform, stdout, stdout, stderr);

    libmu::api::eval(env, libmu::api::read_string(
                              env, "(load \"/opt/gyre/src/core/mu.l\")"));
  }

 private:
  Platform* platform;
  Platform::StreamId stdout;
  Platform::StreamId stderr;
  void* env;
};

}  // namespace gyreui

#endif /* _GYREUI_SRC_UI_GYREENV_H_ */
