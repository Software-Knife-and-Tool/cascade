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
#ifndef _GYREIDE_SRC_UI_LOGICA_H_
#define _GYREIDE_SRC_UI_LOGICA_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <QString>

#include "libmu/libmu.h"
#include "ComposerFrame.h"

namespace gyreide {

class ComposerFrame;
  
class Logica {
 public:
  void Write(QString str) {
    QByteArray ba = str.toLocal8Bit();
    const char *c_str = ba.data();

    write(logica, c_str, strlen(c_str));
  }

  QString Read() {
    int ch;
    QString out;

    while (read(composer, &ch, 1) >= 0)
      out.push_back((char)ch);
    
    return out;
  }

  Logica() : platform(new platform::Platform()) {
    const char* args[]{"pipe-mu", NULL};

    mkfifo(in_fifo, 0755);
    mkfifo(out_fifo,0755);

    logica = open(in_fifo, O_RDONLY | O_NONBLOCK);
    composer = open(out_fifo, O_WRONLY | O_NONBLOCK);

    int pid;
    
    switch (pid = fork()) {
      case 0: {   /* child */
        int composer = open(out_fifo, O_RDONLY | O_NONBLOCK);
        int logica = open(in_fifo, O_WRONLY | O_NONBLOCK);

        dup2(0, composer);
        dup2(1, logica);
        dup2(2, logica);
        // execv("/usr/local/logica/bin/pipe-mu", const_cast<char**>(args));
        execv("/bin/cp", const_cast<char**>(args));
        break;
      }
      case -1: /* error when forking, parent */
        assert(false);
        break;
      default: /* parent */
        unlink(in_fifo);
        unlink(out_fifo);
        break;
    }
  }

 private:
  const char* in_fifo = "/tmp/from-logica";
  const char* out_fifo = "/tmp/to-logica";
  
  platform::Platform* platform;

  int composer;
  int logica;
};

} /* gyreide namespace */

#endif /* _GYREIDE_SRC_UI_LOGICA_H_ */ 
