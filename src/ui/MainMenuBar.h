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
#include "FileMenu.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

namespace gyreui {

class MainWindow;
class FileMenu;

class MainMenuBar : public QMenu {
  Q_OBJECT

 public:
  MainMenuBar(MainWindow*);

  QMenuBar* menu_bar() { return mb; }
  
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

  // help menu
  void about();
  void prefs();

 private:
  template<typename SLOTFN>
  QAction* defAction(const char* label,
                     QKeySequence::StandardKey key,
                     const char* tooltip,
                     SLOTFN fn) {
      auto action = new QAction(tr(label), this);
      action->setShortcuts(key);
      action->setStatusTip(tr(tooltip));
      connect(action, &QAction::triggered, this, fn);

      return action;
  }
  
  QMenu *fileMenu;
  QMenu *editMenu;
  QMenu *helpMenu;
  QMenu *viewMenu;

private:
  MainWindow* mw;
  QMenuBar* mb;
  FileMenu* fm;
};

}  // namespace gyreui

#endif /* _GYREUI_SRC_UI_MAINMENUBAR_H_ */
