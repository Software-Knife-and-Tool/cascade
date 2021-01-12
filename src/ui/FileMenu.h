/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  FileMenu.h: FileMenu class
 **
 **/
#ifndef GYREUI_UI_FILEMENU_H_
#define GYREUI_UI_FILEMENU_H_

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

class FileMenu : public QMenu {
  Q_OBJECT

 public:
  void newFile();
  void openFile();
  void saveFile();
  void printFile();

  explicit FileMenu(MainMenuBar*);

 private:
  MainMenuBar* mb;
  MainWindow* mw;
};

} /* namespace gyreui */

#endif /* GYREUI_UI_FILEMENU_H_ */
