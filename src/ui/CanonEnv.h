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
 **  CanonEnv.h: Canon environment class
 **
 **/
#ifndef _LOGICAIDE_SRC_UI_CANONENV_H_
#define _LOGICAIDE_SRC_UI_CANONENV_H_

#include <QString>

#include "libmu/libmu.h"

namespace logicaide {
  
class CanonEnv {
 public:
  QString version() {

    return QString(libmu_version().c_str());  
  }

  QString rep(QString form) {
    auto rval = libmu_eval(env, libmu_read(env, form.toStdString()));

    return
      QString::fromStdString(
        platform::Platform::GetStdString(stdout) +
        libmu_printToString(env, rval, true));
  }

  QString withException(std::function<void()> fn) {
    libmu->withException(libmu.get(),
                         [fn](void*) { (void)fn(); });
    return
      QString::fromStdString(
        platform::Platform::GetStdString(stderr));
  }
  
  CanonEnv() : platform(new platform::Platform()) {
    stdout = platform::Platform::OpenOutputString("");
    stderr = platform::Platform::OpenOutputString("");
    env = libmu_env_default(platformm stdout, stdout, stderr);

    libmu_eval(env, libmu_read(env, "(load \"/usr/local/logica/mu/mu.l\")"));
    libmu_eval(env, libmu_read(env, "(:defcon lib-base \"/usr/local/logica\")"));
    libmu_eval(env, libmu_read(env, "(load-once logica/library \"/canon/lib.l\")"));
  }

 private:
  platform::Platform* platform;
  platform::Platform::StreamId stdout;
  platform::Platform::StreamId stderr;
  void* env;
};

} /* logicaide namespace */

#endif /* _LOGICAIDE_SRC_UI_CANONENV_H_ */ 
