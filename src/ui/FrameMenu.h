/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  FrameMenu.h: FrameMenu class
 **
 **/
#ifndef GYREUI_UI_FRAMEMENU_H_
#define GYREUI_UI_FRAMEMENU_H_

#include <QMainWindow>
#include <QMenu>

#include "MainMenuBar.h"
#include "MainWindow.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

namespace gyreui {

class MainMenuBar;
class MainWindow;

class FrameMenu : public QMenu {
  Q_OBJECT

 public:
  void envFrame();

  explicit FrameMenu(MainMenuBar*);

 private:
  MainMenuBar* mb;
  MainWindow* mw;
};

} /* namespace gyreui */

#endif /* GYREUI_UI_FRAMEMENU_H_ */
