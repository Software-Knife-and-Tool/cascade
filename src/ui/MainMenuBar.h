/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  MainMenuBar.h: MainMenuBar class
 **
 **/
#ifndef _GYREIDE_SRC_UI_MAINMENUBAR_H_
#define _GYREIDE_SRC_UI_MAINMENUBAR_H_

#include <QMainWindow>
#include <QMenu>

#include "MainWindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

namespace gyreide {

class MainWindow;
  
class MainMenuBar : public QMenu {

 Q_OBJECT

 public:
  MainMenuBar(MainWindow*);

  QMenuBar* menu_bar() {
    return mb;
  }

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
  QMenuBar* mb;
};

} /* gyreide namespace */

#endif  /* _GYREIDE_SRC_UI_MAINMENUBAR_H_ */
