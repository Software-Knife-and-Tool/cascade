/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  FileView.cpp: FileView class
 **
 **/
#include <QDate>
#include <QFileDialog>
#include <QLabel>
#include <QScrollArea>
#include <QString>
#include <QTextEdit>
#include <QToolBar>
#include <QtWidgets>

#include "FileView.h"
#include "MainWindow.h"

namespace gyreui {

void FileView::newFile() { mw->setContextStatus("<b>File|New</b>"); }

void FileView::openFile() {
  mw->setContextStatus("<b>File|Open</b>");

  auto loadFileName = QFileDialog::getOpenFileName(
      this, tr("Load File"), mw->userInfo()->userdir(), tr("File (*)"));

  QFile f(loadFileName);
  if (f.open(QFile::ReadOnly | QFile::Text)) {
    QTextStream in(&f);
    // scratchText->setText(in.readAll());
    f.close();
  }
}

void FileView::saveFile() { mw->setContextStatus("<b>File|Save</b>"); }
void FileView::printFile() { mw->setContextStatus("<b>File|Print</b>"); }

FileView::FileView(QString name, MainWindow* mw) : mw(mw) {
#if 0
  toolBar = new QToolBar();

  connect(toolBar->addAction(tr("clear")), &QAction::triggered, this,
          &ScratchpadFrame::clear);
  connect(toolBar->addAction(tr("load")), &QAction::triggered, this,
          &ScratchpadFrame::load);
  connect(toolBar->addAction(tr("append")), &QAction::triggered, this,
          &ScratchpadFrame::append);
  connect(toolBar->addAction(tr("save")), &QAction::triggered, this,
          &ScratchpadFrame::save);
  connect(toolBar->addAction(tr("save as")), &QAction::triggered, this,
          &ScratchpadFrame::save_as);
  connect(toolBar->addAction(tr("del")), &QAction::triggered, this,
          &ScratchpadFrame::del);
#endif

  fileText = new QTextEdit();
  fileText->setAlignment(Qt::AlignTop);

  scrollArea = new QScrollArea();
  scrollArea->setWidget(fileText);
  scrollArea->setWidgetResizable(true);
  scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

  QSizePolicy spFile(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spFile.setVerticalStretch(1);
  fileText->setSizePolicy(spFile);

  auto layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  // layout->addWidget(toolBar);
  layout->addWidget(scrollArea);

  this->setLayout(layout);
}

} /* namespace gyreui */
