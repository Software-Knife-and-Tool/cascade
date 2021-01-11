/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  gyre.h: Gyre class
 **
 **/
#ifndef GYREUI_UI_GYRE_H_
#define GYREUI_UI_GYRE_H_

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <QString>

#include "ComposerFrame.h"
#include "libmu/libmu.h"

namespace gyreui {

class ComposerFrame;

class Gyre {
 public:
  void Write(QString str) {
    QByteArray ba = str.toLocal8Bit();
    const char* c_str = ba.data();

    write(logica, c_str, strlen(c_str));
  }

  QString Read() {
    int ch;
    QString out;

    while (read(composer, &ch, 1) >= 0) out.push_back((char)ch);

    return out;
  }

  Gyre() : platform(new platform::Platform()) {
    const char* args[]{"pipe-mu", NULL};

    mkfifo(in_fifo, 0755);
    mkfifo(out_fifo, 0755);

    logica = open(in_fifo, O_RDONLY | O_NONBLOCK);
    composer = open(out_fifo, O_WRONLY | O_NONBLOCK);

    int pid;

    switch (pid = fork()) {
      case 0: { /* child */
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
  int gyre;
};

}  // namespace gyreui

#endif /* GYREUI_UI_GYRE_H_ */
