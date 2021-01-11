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
#ifndef GYREUI_UI_MAINMENUBAR_H_
#define GYREUI_UI_MAINMENUBAR_H_

#include <QMainWindow>
#include <QMenu>

#include "FileMenu.h"
#include "MainWindow.h"

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
  MainWindow* mw_() { return this->mw; }

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
  template <typename SLOTFN>
  QAction* defAction(const char* label, QKeySequence key, const char* tooltip,
                     SLOTFN fn) {
    auto action = new QAction(tr(label), this);
    action->setShortcut(key);
    action->setStatusTip(tr(tooltip));
    connect(action, &QAction::triggered, this, fn);

    return action;
  }

  QMenu* fileMenu;
  QMenu* editMenu;
  QMenu* helpMenu;
  QMenu* viewMenu;
  QMenu* frameMenu;

 private:
  MainWindow* mw;
  QMenuBar* mb;
  FileMenu* fm;
};

}  // namespace gyreui

#endif /* GYREUI_UI_MAINMENUBAR_H_ */
