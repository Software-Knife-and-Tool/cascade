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
#ifndef _GYREUI_SRC_UI_FILEMENU_H_
#define _GYREUI_SRC_UI_FILEMENU_H_

#include <QMainWindow>
#include <QMenu>

#include "MainWindow.h"
#include "MainMenuBar.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

namespace gyreui {

class MainWindow;
class MainMenuBar;

class FileMenu : public QMenu {
  Q_OBJECT

 public:
  void newFile() { mw->setContextStatus("Invoked <b>File|New</b>"); }
  void openFile() { mw->setContextStatus("Invoked <b>File|Open</b>"); }
  void saveFile() { mw->setContextStatus("Invoked <b>File|Save</b>"); }
  void printFile() { mw->setContextStatus("Invoked <b>File|Print</b>"); }
  
  explicit FileMenu(MainWindow* mw, MainMenuBar* mb) : mb(mb), mw(mw) { }
  
 private:
  MainMenuBar* mb;
  MainWindow* mw;
};

}  // namespace gyreui

#endif /* _GYREUI_SRC_UI_FILEMENU_H_ */
