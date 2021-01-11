/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  MainMenuBar.cpp: MainMenuBar class
 **
 **/
#include <QtWidgets>

#include "MainMenuBar.h"
#include "MainWindow.h"

namespace gyreui {

void MainMenuBar::newFile() { mw->setContextStatus("Invoked <b>File|New</b>"); }
void MainMenuBar::open() { mw->setContextStatus("Invoked <b>File|Open</b>"); }
void MainMenuBar::save() { mw->setContextStatus("Invoked <b>File|Save</b>"); }
void MainMenuBar::print() { mw->setContextStatus("Invoked <b>File|Print</b>"); }
void MainMenuBar::undo() { mw->setContextStatus("Invoked <b>Edit|Undo</b>"); }
void MainMenuBar::redo() { mw->setContextStatus("Invoked <b>Edit|Redo</b>"); }
void MainMenuBar::cut() { mw->setContextStatus("Invoked <b>Edit|Cut</b>"); }
void MainMenuBar::copy() { mw->setContextStatus("Invoked <b>Edit|Copy</b>"); }
void MainMenuBar::paste() { mw->setContextStatus("Invoked <b>Edit|Paste</b>"); }
void MainMenuBar::about() {
  mw->setContextStatus("Invoked <b>Help|About</b>");
  QMessageBox::about(this, tr("About Gyre-UI"),
                     tr("The <b>Menu</b> example shows how to create "
                        "menu-bar menus and context menus."));
}
void MainMenuBar::prefs() { mw->setContextStatus("Invoked <b>Help|prefs</b>"); }

MainMenuBar::MainMenuBar(MainWindow *mw) : mw(mw) {
  mb = new QMenuBar(this);

  fileMenu = addMenu(tr("&File"));
  fileMenu->addAction(defAction("&New", QKeySequence::New, "Create new file", &MainMenuBar::newFile));
  fileMenu->addAction(defAction("&Open...", QKeySequence::Open, "Open an existing file", &MainMenuBar::open));
  fileMenu->addAction(defAction("&Save", QKeySequence::Save, "Save the document to disk", &MainMenuBar::save));
  fileMenu->addAction(defAction("&Print...", QKeySequence::Print, "Print the document", &MainMenuBar::print));
  fileMenu->addSeparator();
  fileMenu->addAction(defAction("&Exit", QKeySequence::Quit, "Exit the application", &QWidget::close));

  editMenu = addMenu(tr("&Edit"));
  editMenu->addAction(defAction("&Undo", QKeySequence::Undo, "Undo the last operation", &MainMenuBar::undo));
  editMenu->addAction(defAction("&Redo", QKeySequence::Redo, "Redo the last operation", &MainMenuBar::redo));
  editMenu->addSeparator();
  editMenu->addAction(defAction("&Cut", QKeySequence::Cut, "Cut the current selection", &MainMenuBar::cut));
  editMenu->addAction(defAction("&Copy", QKeySequence::Copy, "Copy the current selection", &MainMenuBar::copy));
  editMenu->addAction(defAction("&Paste", QKeySequence::Paste, "Paste the clipboard", &MainMenuBar::paste));
  editMenu->addSeparator();

  viewMenu = addMenu(tr("&View"));
  viewMenu->addAction(defAction("&environment", QKeySequence::Undo, "Undo the last operation", &MainMenuBar::undo));
  viewMenu->addAction(defAction("&file system", QKeySequence::Redo, "Redo the last operation", &MainMenuBar::redo));
  viewMenu->addAction(defAction("&debugger", QKeySequence::Cut, "Cut the current selection", &MainMenuBar::cut));
  viewMenu->addAction(defAction("&inspector", QKeySequence::Copy, "Copy the current selection", &MainMenuBar::copy));
  viewMenu->addAction(defAction("&listener", QKeySequence::Paste, "Paste the clipboard", &MainMenuBar::paste));
  viewMenu->addAction(defAction("&notifications", QKeySequence::Paste, "Paste the clipboard", &MainMenuBar::paste));
  viewMenu->addAction(defAction("&system", QKeySequence::Paste, "Paste the clipboard", &MainMenuBar::paste));
  
  helpMenu = addMenu(tr("&Help"));
  helpMenu->addAction(defAction("&About", QKeySequence::WhatsThis, "Show the About box", &MainMenuBar::about));
  helpMenu->addAction(defAction("&Preferences", QKeySequence::Preferences, "Show the prefs panel", &MainMenuBar::prefs));

  mb->addMenu(fileMenu);
  mb->addMenu(editMenu);
  mb->addMenu(viewMenu);
  mb->addMenu(helpMenu);
}

}  // namespace gyreui
