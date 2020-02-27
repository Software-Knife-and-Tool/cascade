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
 **  LocusFrame.h: LocusFrame class
 **
 **/

#ifndef _LOCUS_SRC_LOCUS_LOCUSFRAME_H_
#define _LOCUS_SRC_LOCUS_LOCUSFRAME_H_

#include <QWidget>
#include <QFrame>

#include "ConsoleWidget.h"
#include "MainWindow.h"
#include "Mu.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QWidget;
class QLabel;
QT_END_NAMESPACE

class ConsoleWidget;

namespace locus {
  
class LocusFrame : public QFrame {

  Q_OBJECT

 public:
  LocusFrame(MainWindow*);

 protected:

 private:
  QVBoxLayout *layout;
  ConsoleWidget *consoleWidget;
  QLabel *bannerLabel;
  Mu* mu;
};

} /* locus namespace */

#endif  /* _LOCUS_SRC_LOCUS_LOCUSFRAME_H_ */
