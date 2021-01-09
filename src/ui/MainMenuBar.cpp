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

// file menu
void MainMenuBar::newFile() { mw->setContextStatus("Invoked <b>File|New</b>"); }
void MainMenuBar::open() { mw->setContextStatus("Invoked <b>File|Open</b>"); }
void MainMenuBar::save() { mw->setContextStatus("Invoked <b>File|Save</b>"); }
void MainMenuBar::print() { mw->setContextStatus("Invoked <b>File|Print</b>"); }

// edit menu
void MainMenuBar::undo() { mw->setContextStatus("Invoked <b>Edit|Undo</b>"); }
void MainMenuBar::redo() { mw->setContextStatus("Invoked <b>Edit|Redo</b>"); }
void MainMenuBar::cut() { mw->setContextStatus("Invoked <b>Edit|Cut</b>"); }
void MainMenuBar::copy() { mw->setContextStatus("Invoked <b>Edit|Copy</b>"); }
void MainMenuBar::paste() { mw->setContextStatus("Invoked <b>Edit|Paste</b>"); }

void MainMenuBar::bold() {
  mw->setContextStatus("Invoked <b>Edit|Format|Bold</b>");
}

void MainMenuBar::italic() {
  mw->setContextStatus("Invoked <b>Edit|Format|Italic</b>");
}

void MainMenuBar::leftAlign() {
  mw->setContextStatus("Invoked <b>Edit|Format|Left Align</b>");
}

void MainMenuBar::rightAlign() {
  mw->setContextStatus("Invoked <b>Edit|Format|Right Align</b>");
}

void MainMenuBar::justify() {
  mw->setContextStatus("Invoked <b>Edit|Format|Justify</b>");
}

void MainMenuBar::center() {
  mw->setContextStatus("Invoked <b>Edit|Format|Center</b>");
}

void MainMenuBar::setLineSpacing() {
  mw->setContextStatus("Invoked <b>Edit|Format|Set Line Spacing</b>");
}

void MainMenuBar::setParagraphSpacing() {
  mw->setContextStatus("Invoked <b>Edit|Format|Set Paragraph Spacing</b>");
}

// help
void MainMenuBar::about() {
  mw->setContextStatus("Invoked <b>Help|About</b>");
  QMessageBox::about(this, tr("About Menu"),
                     tr("The <b>Menu</b> example shows how to create "
                        "menu-bar menus and context menus."));
}

void MainMenuBar::createActions() {
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

  undoAct = new QAction(tr("&Undo"), this);
  undoAct->setShortcuts(QKeySequence::Undo);
  undoAct->setStatusTip(tr("Undo the last operation"));
  connect(undoAct, &QAction::triggered, this, &MainMenuBar::undo);

  redoAct = new QAction(tr("&Redo"), this);
  redoAct->setShortcuts(QKeySequence::Redo);
  redoAct->setStatusTip(tr("Redo the last operation"));
  connect(redoAct, &QAction::triggered, this, &MainMenuBar::redo);

  cutAct = new QAction(tr("&Cut"), this);
  cutAct->setShortcuts(QKeySequence::Cut);
  cutAct->setStatusTip(
      tr("Cut the current selection's contents to the "
         "clipboard"));
  connect(cutAct, &QAction::triggered, this, &MainMenuBar::cut);

  copyAct = new QAction(tr("&Copy"), this);
  copyAct->setShortcuts(QKeySequence::Copy);
  copyAct->setStatusTip(
      tr("Copy the current selection's contents to the "
         "clipboard"));
  connect(copyAct, &QAction::triggered, this, &MainMenuBar::copy);

  pasteAct = new QAction(tr("&Paste"), this);
  pasteAct->setShortcuts(QKeySequence::Paste);
  pasteAct->setStatusTip(
      tr("Paste the clipboard's contents into the current "
         "selection"));
  connect(pasteAct, &QAction::triggered, this, &MainMenuBar::paste);

  // prefs
  prefsAct = new QAction(tr("&Preferences"), this);
  prefsAct->setShortcuts(QKeySequence::Paste);
  prefsAct->setStatusTip(tr("Show the preferences panel"));
  connect(prefsAct, &QAction::triggered, this, &MainMenuBar::paste);

  boldAct = new QAction(tr("&Bold"), this);
  boldAct->setCheckable(true);
  boldAct->setShortcut(QKeySequence::Bold);
  boldAct->setStatusTip(tr("Make the text bold"));
  connect(boldAct, &QAction::triggered, this, &MainMenuBar::bold);

  QFont boldFont = boldAct->font();
  boldFont.setBold(true);
  boldAct->setFont(boldFont);

  italicAct = new QAction(tr("&Italic"), this);
  italicAct->setCheckable(true);
  italicAct->setShortcut(QKeySequence::Italic);
  italicAct->setStatusTip(tr("Make the text italic"));
  connect(italicAct, &QAction::triggered, this, &MainMenuBar::italic);

  QFont italicFont = italicAct->font();
  italicFont.setItalic(true);
  italicAct->setFont(italicFont);

  setLineSpacingAct = new QAction(tr("Set &Line Spacing..."), this);
  setLineSpacingAct->setStatusTip(
      tr("Change the gap between the lines of a "
         "paragraph"));
  connect(setLineSpacingAct, &QAction::triggered, this,
          &MainMenuBar::setLineSpacing);

  setParagraphSpacingAct = new QAction(tr("Set &Paragraph Spacing..."), this);
  setParagraphSpacingAct->setStatusTip(tr("Change the gap between paragraphs"));
  connect(setParagraphSpacingAct, &QAction::triggered, this,
          &MainMenuBar::setParagraphSpacing);

  aboutAct = new QAction(tr("&About"), this);
  aboutAct->setStatusTip(tr("Show the application's About box"));
  connect(aboutAct, &QAction::triggered, this, &MainMenuBar::about);

  leftAlignAct = new QAction(tr("&Left Align"), this);
  leftAlignAct->setCheckable(true);
  leftAlignAct->setShortcut(tr("Ctrl+L"));
  leftAlignAct->setStatusTip(tr("Left align the selected text"));
  connect(leftAlignAct, &QAction::triggered, this, &MainMenuBar::leftAlign);

  rightAlignAct = new QAction(tr("&Right Align"), this);
  rightAlignAct->setCheckable(true);
  rightAlignAct->setShortcut(tr("Ctrl+R"));
  rightAlignAct->setStatusTip(tr("Right align the selected text"));
  connect(rightAlignAct, &QAction::triggered, this, &MainMenuBar::rightAlign);

  justifyAct = new QAction(tr("&Justify"), this);
  justifyAct->setCheckable(true);
  justifyAct->setShortcut(tr("Ctrl+J"));
  justifyAct->setStatusTip(tr("Justify the selected text"));
  connect(justifyAct, &QAction::triggered, this, &MainMenuBar::justify);

  centerAct = new QAction(tr("&Center"), this);
  centerAct->setCheckable(true);
  centerAct->setShortcut(tr("Ctrl+E"));
  centerAct->setStatusTip(tr("Center the selected text"));
  connect(centerAct, &QAction::triggered, this, &MainMenuBar::center);

  alignmentGroup = new QActionGroup(this);
  alignmentGroup->addAction(leftAlignAct);
  alignmentGroup->addAction(rightAlignAct);
  alignmentGroup->addAction(justifyAct);
  alignmentGroup->addAction(centerAct);
  leftAlignAct->setChecked(true);
}

void MainMenuBar::createMenus() {
  fileMenu = addMenu(tr("&File"));
  fileMenu->addAction(newAct);
  fileMenu->addAction(openAct);
  fileMenu->addAction(saveAct);
  fileMenu->addAction(printAct);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);

  /* fileMenu is a sub-menu of editMenu */
  editMenu = addMenu(tr("&Edit"));
  editMenu->addAction(undoAct);
  editMenu->addAction(redoAct);
  editMenu->addSeparator();
  editMenu->addAction(cutAct);
  editMenu->addAction(copyAct);
  editMenu->addAction(pasteAct);
  editMenu->addSeparator();

  formatMenu = editMenu->addMenu(tr("&Format"));
  formatMenu->addAction(boldAct);
  formatMenu->addAction(italicAct);
  formatMenu->addSeparator()->setText(tr("Alignment"));
  formatMenu->addAction(leftAlignAct);
  formatMenu->addAction(rightAlignAct);
  formatMenu->addAction(justifyAct);
  formatMenu->addAction(centerAct);
  formatMenu->addSeparator();
  formatMenu->addAction(setLineSpacingAct);
  formatMenu->addAction(setParagraphSpacingAct);

  /* this ends up in the ui main menu */
  helpMenu = addMenu(tr("&Help"));
  helpMenu->addAction(aboutAct);
  helpMenu->addAction(prefsAct);
}

MainMenuBar::MainMenuBar(MainWindow *mw) : mw(mw) {
  createActions();
  createMenus();

  mb = new QMenuBar(this);
  mb->addMenu(fileMenu);
  mb->addMenu(editMenu);
  mb->addMenu(formatMenu);
  mb->addMenu(helpMenu);
}

}  // namespace gyreui
