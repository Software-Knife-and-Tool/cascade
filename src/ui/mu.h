/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  mu.h: Mu class
 **
 **/
#ifndef GYREUI_UI_MU_H_
#define GYREUI_UI_MU_H_

#include <QString>

#include "libmu/libmu.h"

namespace gyreui {

using libmu::platform::Platform;

class Mu {
 public:
  QString version() { return QString(libmu::api::version()); }

  QString mu(QString form) {
    auto rval =
        libmu::api::eval(env, libmu::api::read_string(env, form.toStdString()));

    return QString::fromStdString(Platform::GetStdString(stdout) +
                                  libmu::api::print_cstr(env, rval, true));
  }

  QString withException(std::function<void()> fn) {
    libmu::api::withException(env, [fn](void*) { (void)fn(); });
    return QString::fromStdString(Platform::GetStdString(stderr));
  }

  Mu() : platform(new Platform()) {
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

#endif /* GYREUI_UI_MU_H_ */
