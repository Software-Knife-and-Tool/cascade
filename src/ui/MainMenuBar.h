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

#include "FileView.h"
#include "FrameMenu.h"
#include "MainWindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

namespace gyreui {

class FileView;
class FrameMenu;
class MainWindow;

class MainMenuBar : public QMenu {
  Q_OBJECT

 public:
  MainMenuBar(MainWindow*);

  QWidget* defaultView();
  QMenuBar* menu_bar() { return mb; }
  MainWindow* mw_() { return this->mw; }

 private slots:
  /* file menu */
  void newFile();
  void openFile();
  void saveFile();
  void printFile();

  /* edit menu */
  void undoEdit();
  void redoEdit();
  void cutEdit();
  void copyEdit();
  void pasteEdit();

  /* frame menu */
  void envFrame();
  void fsiFrame();
  void dbgFrame();
  void insFrame();
  void lstFrame();
  void notFrame();
  void sysFrame();

  /* help menu */
  void aboutHelp();
  void prefsHelp();

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
  FileView* fv;
  FrameMenu* fm;
};

} /* namespace gyreui */

#endif /* GYREUI_UI_MAINMENUBAR_H_ */
