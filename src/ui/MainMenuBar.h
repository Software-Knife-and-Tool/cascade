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
 **  MainMenuBar.h: MainMenuBar class
 **
 **/
#ifndef _LOGICAIDE_SRC_UI_MAINMENUBAR_H_
#define _LOGICAIDE_SRC_UI_MAINMENUBAR_H_

#include <QMainWindow>
#include <QMenu>

#include "MainWindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

namespace composer {

class MainWindow;
  
class MainMenuBar : public QMenu {

 Q_OBJECT

 public:
  MainMenuBar(MainWindow*);

  QAction *cutAct;
  QAction *copyAct;
  QAction *pasteAct;

 private slots:
  void newFile();
  void open();
  void save();
  void print();
  void undo();
  void redo();
  void cut();
  void copy();
  void paste();
  void bold();
  void italic();
  void leftAlign();
  void rightAlign();
  void justify();
  void center();
  void setLineSpacing();
  void setParagraphSpacing();
  void about();

 private:
  void createActions();
  void createMenus();

  QMenu *fileMenu;
  QMenu *editMenu;
  QMenu *formatMenu;
  QMenu *helpMenu;

  QActionGroup *alignmentGroup;
  QAction *aboutAct;
  QAction *boldAct;
  QAction *centerAct;
  QAction *exitAct;
  QAction *italicAct;
  QAction *justifyAct;
  QAction *leftAlignAct;
  QAction *newAct;
  QAction *openAct;
  QAction *prefsAct;
  QAction *printAct;
  QAction *redoAct;
  QAction *rightAlignAct;
  QAction *saveAct;
  QAction *scriptAct;
  QAction *setLineSpacingAct;
  QAction *setParagraphSpacingAct;
  QAction *undoAct;

 private:
  MainWindow* mw;
};

} /* composer namespace */

#endif  /* _LOGICAIDE_SRC_UI_MAINMENUBAR_H_ */
