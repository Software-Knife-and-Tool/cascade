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
#ifndef _GYREUI_SRC_UI_MAINMENUBAR_H_
#define _GYREUI_SRC_UI_MAINMENUBAR_H_

#include <QMainWindow>
#include <QMenu>

#include "MainWindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

namespace gyreui {

class MainWindow;

class MainMenuBar : public QMenu {
  Q_OBJECT

 public:
  MainMenuBar(MainWindow *);

  QMenuBar *menu_bar() { return mb; }

  QAction *cutAct;
  QAction *copyAct;
  QAction *pasteAct;

 private slots:
  // file menu
  void newFile();
  void open();
  void save();
  void print();

  // edit menu
  void undo();
  void redo();
  void cut();
  void copy();
  void paste();

  // settings menu
  void bold();
  void italic();
  void leftAlign();
  void rightAlign();
  void justify();
  void center();
  void setLineSpacing();
  void setParagraphSpacing();

  // help menu
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

  // seetings
  QAction *boldAct;
  QAction *centerAct;
  QAction *exitAct;
  QAction *italicAct;
  QAction *justifyAct;
  QAction *leftAlignAct;

  // file menu
  QAction *newAct;
  QAction *openAct;
  QAction *printAct;
  
  QAction *prefsAct;

  QAction *redoAct;
  QAction *rightAlignAct;
  QAction *saveAct;
  QAction *scriptAct;
  QAction *setLineSpacingAct;
  QAction *setParagraphSpacingAct;
  QAction *undoAct;

 private:
  MainWindow *mw;
  QMenuBar *mb;
};

}  // namespace gyreui

#endif /* _GYREUI_SRC_UI_MAINMENUBAR_H_ */
