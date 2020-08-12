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
 **  ComposerFrame.h: ComposerFrame class
 **
 **/
#ifndef _LOGICAIDE_SRC_UI_COMPOSERFRAME_H_
#define _LOGICAIDE_SRC_UI_COMPOSERFRAME_H_

#include <QFrame>
#include <QLabel>
#include <QScrollArea>
#include <QTextEdit>
#include <QToolBar>
#include <QWidget>

#include "canon.h"
#include "MainTabBar.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QScroll;
class QTextEdit;
class QToolBar;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace composer {

class MainTabBar;
class MainWindow;
  
class ComposerFrame : public QFrame {

 Q_OBJECT

 public:
  explicit ComposerFrame(QString, MainTabBar*, Canon*);

  void bufferStatus();
  void clear();
  void eval();
  void load();
  void new_buffer();
  void next();
  void prev();
  void save();
  void save_as();
  void switchBuffer();

  void log(QString msg) { tabBar->log(msg); }
  
  void setContextStatus(QString str) {
    tabBar->setContextStatus(str);
  }

  void showEvent(QShowEvent* event) override {
    QWidget::showEvent(event);
    tabBar->setContextStatus(name);
  }
  
  bool eventFilter(QObject, QEvent*);
  
  struct buffer {
    QString file_name;
    QString text;
  };

  signals:
     void evalHappened(QString);

 private:
  
  const char* style = "color: rgb(0, 0, 0);"
                      "background-color: rgb(255, 255, 255);";

  bool eventFilter(QObject*, QEvent*) override;
  QString loadFileName;
  QString saveFileName;
  std::vector<buffer*> buffers;
  unsigned long bufferCursor;

  MainTabBar *tabBar;
  Canon* canon;
  QString name;
  QTextEdit* edit_text;
  QLabel* eval_text;
  QToolBar* tool_bar;  
  QScrollArea* edit_scroll;
  QScrollArea* eval_scroll;
};

} /* composer namespace */

#endif  /* _LOGICAIDE_SRC_UI_COMPOSERFRAME_H_ */
