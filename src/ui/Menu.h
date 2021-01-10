/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  Menu.h: Menu class
 **
 **/
#ifndef _GYREUI_SRC_UI_MENU_H_
#define _GYREUI_SRC_UI_MENU_H_

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

class MainMenuBar;

class Menu : public QMenu {
  Q_OBJECT

 public:
  explicit Menu(MainMenuBar*, std::vector<QAction*>, );

  struct Action {
    std::string 
  // menu
  fileMenu = addMenu(tr("&File"));
  fileMenu->addAction(newAct);
  fileMenu->addAction(openAct);
  fileMenu->addAction(saveAct);
  fileMenu->addAction(printAct);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);

  // slots
  void MainMenuBar::newFile() { mw->setContextStatus("Invoked <b>File|New</b>"); }
  void MainMenuBar::open() { mw->setContextStatus("Invoked <b>File|Open</b>"); }
  void MainMenuBar::save() { mw->setContextStatus("Invoked <b>File|Save</b>"); }
  void MainMenuBar::print() { mw->setContextStatus("Invoked <b>File|Print</b>"); }

  // actions
  newAct = new QAction(tr("&New"), this);
  newAct->setShortcuts(QKeySequence::New);
  newAct->setStatusTip(tr("Create a new file"));
  connect(newAct, &QAction::triggered, this, &MainMenuBar::newFile);

  openAct = new QAction(tr("&Open..."), this);
  openAct->setShortcuts(QKeySequence::Open);
  openAct->setStatusTip(tr("Open an existing file"));
  connect(openAct, &QAction::triggered, this, &MainMenuBar::open);

  saveAct = new QAction(tr("&Save"), this);
  saveAct->setShortcuts(QKeySequence::Save);
  saveAct->setStatusTip(tr("Save the document to disk"));
  connect(saveAct, &QAction::triggered, this, &MainMenuBar::save);

  printAct = new QAction(tr("&Print..."), this);
  printAct->setShortcuts(QKeySequence::Print);
  printAct->setStatusTip(tr("Print the document"));
  connect(printAct, &QAction::triggered, this, &MainMenuBar::print);

  exitAct = new QAction(tr("&Exit"), this);
  exitAct->setShortcuts(QKeySequence::Quit);
  exitAct->setStatusTip(tr("Exit the application"));
  connect(exitAct, &QAction::triggered, this, &QWidget::close);
};

}  // namespace gyreui

#endif /* _GYREUI_SRC_UI_MENU_H_ */
