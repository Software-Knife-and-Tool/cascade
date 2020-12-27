/*******
 **
 ** Copyright (c) 2017, James M. Putnam
 ** All rights reserved.
 **
 ** Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are met:
 **
 ** 1. Redistributions of source code must retain the above copyright notice,
 **    this list of conditions and the following disclaimer.
 **
 ** 2. Redistributions in binary form must reproduce the above copyright
 **    notice, this list of conditions and the following disclaimer in the
 **    documentation and/or other materials provided with the distribution.
 **
 ** 3. Neither the name of the copyright holder nor the names of its
 **    contributors may be used to endorse or promote products derived from
 **    this software without specific prior written permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 ** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 ** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 ** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 ** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 ** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 ** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 ** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 ** POSSIBILITY OF SUCH DAMAGE.
 **
 *******/

/********
 **
 **  mu.h: Mu class
 **
 **/
#ifndef _GYREIDE_SRC_UI_MU_H_
#define _GYREIDE_SRC_UI_MU_H_

#include <QString>

#include "libmu/libmu.h"

namespace gyreide {
  
using libmu::platform::Platform;  

class Mu {
 public:
  QString version() {
    return QString(libmu::api::version());  
  }

  QString mu(QString form) {
    auto rval =
      libmu::api::eval(env, libmu::api::read_string(env, form.toStdString()));
    
    return
      QString::fromStdString(
        Platform::GetStdString(stdout) +
        libmu::api::print_cstr(env, rval, true));
  }

  QString withException(std::function<void()> fn) {
    libmu::api::withException(env,
                         [fn](void*) { (void)fn(); });
    return
      QString::fromStdString(Platform::GetStdString(stderr));
  }
  
  Mu() : platform(new Platform()) {
    stdout = Platform::OpenOutputString("");
    stderr = Platform::OpenOutputString("");
    env = libmu::api::env(platform, stdout, stdout, stderr);
      
    libmu::api::eval(env,
               libmu::api::read_string(env,
                                 "(load \"/opt/gyre/src/core/mu.l\")"));
  }

 private:
  Platform* platform;
  Platform::StreamId stdout;
  Platform::StreamId stderr;
  void* env;
};

} /* gyreide namespace */

#endif /* _GYREIDE_SRC_UI_MU_H_ */ 
