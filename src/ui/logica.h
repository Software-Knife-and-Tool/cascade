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
 **  logica.h: logica class
 **
 **/
#ifndef _CASCADE_SRC_UI_LOGICA_H_
#define _CASCADE_SRC_UI_LOGICA_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <QString>

#include "libmu/libmu.h"
#include "ComposerFrame.h"

namespace composer {

class ComposerFrame;
  
class Logica {
 public:
  void Write(QString) {
    
  }

  QString Read() {

    return QString("logica out");
  }

  Logica(ComposerFrame* frame) : platform(new platform::Platform()) {
    (void)platform::Platform::OpenPipeStream("/tmp/logica", "");

    this->frame = frame;
    this->stdin = open("/tmp/logica", O_RDONLY);
    this->stdout = open("/tmp/logica", O_WRONLY);

    // frame->WriteOut(QString("why rhett..."));
#if 0
    switch (fork()) {
      case 0: { /* child */
        char* args[NULL];

        exit(-1);
        dup2(0, this->stdin);
        dup2(1, this->stdout);
        dup2(2, this->stdout);
        execv("/usr/local/logica/bin/pipe-mu", args);
        assert(false);
        break;
      }
      case -1: /* error forking, parent */
        break;
      default: /* parent */
        break;
    }
#endif
  }

 private:
  ComposerFrame* frame;
  platform::Platform* platform;
  int stdin;
  int stdout;
};

} /* composer namespace */

#endif /* _CASCADE_SRC_UI_LOGICA_H_ */ 
