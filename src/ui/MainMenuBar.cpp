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

#include "FileView.h"
#include "FrameMenu.h"
#include "MainMenuBar.h"
#include "MainWindow.h"

namespace gyreui {

void MainMenuBar::newFile() { fv->newFile(); }
void MainMenuBar::openFile() { fv->openFile(); }
void MainMenuBar::saveFile() { fv->saveFile(); }
void MainMenuBar::printFile() { fv->printFile(); }

void MainMenuBar::envFrame() { fm->envFrame(); }
void MainMenuBar::fsiFrame() { fm->envFrame(); }
void MainMenuBar::dbgFrame() { fm->envFrame(); }
void MainMenuBar::insFrame() { fm->envFrame(); }
void MainMenuBar::lstFrame() { fm->envFrame(); }
void MainMenuBar::notFrame() { fm->envFrame(); }
void MainMenuBar::sysFrame() { fm->sysFrame(); }

void MainMenuBar::undoEdit() {
  mw->setContextStatus("Invoked <b>Edit|Undo</b>");
}
void MainMenuBar::redoEdit() {
  mw->setContextStatus("Invoked <b>Edit|Redo</b>");
}
void MainMenuBar::cutEdit() { mw->setContextStatus("Invoked <b>Edit|Cut</b>"); }

void MainMenuBar::copyEdit() {
  mw->setContextStatus("Invoked <b>Edit|Copy</b>");
}
void MainMenuBar::pasteEdit() {
  mw->setContextStatus("Invoked <b>Edit|Paste</b>");
}

void MainMenuBar::aboutHelp() {
  mw->setContextStatus("Invoked <b>Help|About</b>");
  QMessageBox::about(this, tr("About Gyre-UI"),
                     tr("The <b>Menu</b> example shows how to create "
                        "menu-bar menus and context menus."));
}
void MainMenuBar::prefsHelp() {
  mw->setContextStatus("Invoked <b>Help|prefs</b>");
}

QWidget* MainMenuBar::defaultView() { return fm->defaultView(); }

/** * menu bar constructor **/
MainMenuBar::MainMenuBar(MainWindow* mw)
    : mw(mw), fv(new FileView("", mw)), fm(new FrameMenu(this)) {
  mb = new QMenuBar(this);

  /* on macos, ctrl is cmd and meta is ctrl. pfffft. */
  fileMenu = addMenu(tr("&File"));
  fileMenu->addAction(defAction("&New", QKeySequence::New, "Create new file",
                                &MainMenuBar::newFile));
  fileMenu->addAction(defAction("&Open...", QKeySequence::Open,
                                "Open an existing file",
                                &MainMenuBar::openFile));
  fileMenu->addAction(defAction("&Save", QKeySequence::Save,
                                "Save the document to disk",
                                &MainMenuBar::saveFile));
  fileMenu->addAction(defAction("&Print...", QKeySequence::Print,
                                "Print the document", &MainMenuBar::printFile));
  fileMenu->addSeparator();
  fileMenu->addAction(defAction("&Exit", QKeySequence::Quit,
                                "Exit the application", []() { exit(0); }));

  editMenu = addMenu(tr("&Edit"));
  editMenu->addAction(defAction("&Undo", QKeySequence::Undo,
                                "Undo the last operation",
                                &MainMenuBar::undoEdit));
  editMenu->addAction(defAction("&Redo", QKeySequence::Redo,
                                "Redo the last operation",
                                &MainMenuBar::redoEdit));
  editMenu->addSeparator();
  editMenu->addAction(defAction("&Cut", QKeySequence::Cut,
                                "Cut the current selection",
                                &MainMenuBar::cutEdit));
  editMenu->addAction(defAction("&Copy", QKeySequence::Copy,
                                "Copy the current selection",
                                &MainMenuBar::copyEdit));
  editMenu->addAction(defAction("&Paste", QKeySequence::Paste,
                                "Paste the clipboard",
                                &MainMenuBar::pasteEdit));

  viewMenu = addMenu(tr("&View"));
  viewMenu->addAction(defAction("&split screen", QKeySequence::UnknownKey,
                                "split screen", []() {}));

  frameMenu = addMenu(tr("&Frame"));
  frameMenu->addAction(defAction("&environment", QKeySequence(tr("Ctrl+1", "")),
                                 "environment", &MainMenuBar::envFrame));
  frameMenu->addAction(defAction("&file system", QKeySequence(tr("Ctrl+2", "")),
                                 "file system", []() {}));
  frameMenu->addAction(defAction("&debugger", QKeySequence(tr("Ctrl+3", "")),
                                 "debugger", []() {}));
  frameMenu->addAction(defAction("&inspector", QKeySequence(tr("Ctrl+4", "")),
                                 "inspector", []() {}));
  frameMenu->addAction(defAction("&listener", QKeySequence(tr("Ctrl+5", "")),
                                 "listener", []() {}));
  frameMenu->addAction(defAction("&notifications",
                                 QKeySequence(tr("Ctrl+6", "")),
                                 "notifications", []() {}));
  frameMenu->addAction(defAction("&system", QKeySequence(tr("Ctrl+7", "")),
                                 "system inspector", &MainMenuBar::sysFrame));

  helpMenu = addMenu(tr("&Help"));
  helpMenu->addAction(defAction("&About", QKeySequence::WhatsThis,
                                "Show the About box", &MainMenuBar::aboutHelp));
  helpMenu->addAction(defAction("&Preferences", QKeySequence::Preferences,
                                "Show the prefs panel", []() {}));

  mb->addMenu(fileMenu);
  mb->addMenu(editMenu);
  mb->addMenu(viewMenu);
  mb->addMenu(frameMenu);
  mb->addMenu(helpMenu);
}

} /* namespace gyreui */
