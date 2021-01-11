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

#include "FileMenu.h"
#include "MainMenuBar.h"
#include "MainWindow.h"

namespace gyreui {

void MainMenuBar::newFile() {
  mw->setContextStatus("<b>File|New</b>");
  fm->newFile();
}
void MainMenuBar::open() {
  mw->setContextStatus("<b>File|Open</b>");
  fm->openFile();
}
void MainMenuBar::save() {
  mw->setContextStatus("<b>File|Save</b>");
  fm->saveFile();
}
void MainMenuBar::print() {
  mw->setContextStatus("<b>File|Print</b>");
  fm->printFile();
}
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

MainMenuBar::MainMenuBar(MainWindow *mw) : mw(mw), fm(new FileMenu(this)) {
  mb = new QMenuBar(this);

  // on macos, ctrl is cmd and meta is ctrl. pfffft.
  fileMenu = addMenu(tr("&File"));
  fileMenu->addAction(defAction("&New", QKeySequence::New, "Create new file", &MainMenuBar::newFile));
  fileMenu->addAction(defAction("&Open...", QKeySequence::Open, "Open an existing file", &MainMenuBar::open));
  fileMenu->addAction(defAction("&Save", QKeySequence::Save, "Save the document to disk", &MainMenuBar::save));
  fileMenu->addAction(defAction("&Print...", QKeySequence::Print, "Print the document", &MainMenuBar::print));
  fileMenu->addSeparator();
  fileMenu->addAction(defAction("&Exit", QKeySequence::Quit, "Exit the application", []() { exit(0); }));

  editMenu = addMenu(tr("&Edit"));
  editMenu->addAction(defAction("&Undo", QKeySequence::Undo, "Undo the last operation", &MainMenuBar::undo));
  editMenu->addAction(defAction("&Redo", QKeySequence::Redo, "Redo the last operation", &MainMenuBar::redo));
  editMenu->addSeparator();
  editMenu->addAction(defAction("&Cut", QKeySequence::Cut, "Cut the current selection", &MainMenuBar::cut));
  editMenu->addAction(defAction("&Copy", QKeySequence::Copy, "Copy the current selection", &MainMenuBar::copy));
  editMenu->addAction(defAction("&Paste", QKeySequence::Paste, "Paste the clipboard", &MainMenuBar::paste));
  editMenu->addSeparator();

  viewMenu = addMenu(tr("&View"));
  viewMenu->addAction(defAction("&split screen", QKeySequence::UnknownKey, "split screen", [](){}));
  
  frameMenu = addMenu(tr("&Frames"));
  frameMenu->addAction(defAction("&environment", QKeySequence(tr("Ctrl+1", "")), "environment", [](){}));
  frameMenu->addAction(defAction("&file system", QKeySequence(tr("Ctrl+2", "")), "file system", [](){}));
  frameMenu->addAction(defAction("&debugger", QKeySequence(tr("Ctrl+3", "")), "debugger", [](){}));
  frameMenu->addAction(defAction("&inspector", QKeySequence(tr("Ctrl+4", "")), "inspector", [](){}));
  frameMenu->addAction(defAction("&listener", QKeySequence(tr("Ctrl+5", "")), "listener", [](){}));
  frameMenu->addAction(defAction("&notifications", QKeySequence(tr("Ctrl+6", "")), "notifications", [](){}));
  frameMenu->addAction(defAction("&system", QKeySequence(tr("Ctrl+7", "")), "system inspector", [](){}));
  
  helpMenu = addMenu(tr("&Help"));
  helpMenu->addAction(defAction("&About", QKeySequence::WhatsThis, "Show the About box", &MainMenuBar::about));
  helpMenu->addAction(defAction("&Preferences", QKeySequence::Preferences, "Show the prefs panel", [](){}));

  mb->addMenu(fileMenu);
  mb->addMenu(editMenu);
  mb->addMenu(viewMenu);
  mb->addMenu(frameMenu);
  mb->addMenu(helpMenu);
}

}  // namespace gyreui
