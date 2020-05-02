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
 **  CascadeFrame.h: CascadeFrame class
 **
 **/
#ifndef _CASCADE_SRC_UI_CASCADEFRAME_H_
#define _CASCADE_SRC_UI_CASCADEFRAME_H_

#include <QFrame>
#include <QMdiArea>
#include <QWidget>

#include "ConsoleWidget.h"
#include "MainTabBar.h"
#include "Mu.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QWidget;
class QLabel;
QT_END_NAMESPACE

class ConsoleWidget;

namespace cascade {

class MainTabBar;
  
class CascadeFrame : public QFrame {
  Q_OBJECT

 public:
  CascadeFrame(QWidget*);

 protected:

 private:
  Mu* mu;
  ConsoleWidget* consoleWidget;
  QLabel* bannerLabel;
  QVBoxLayout* layout;
};

} /* cascade namespace */

#endif  /* _CASCADE_SRC_UI_CASCADEFRAME_H_ */
