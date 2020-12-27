/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  ScratchpadFrame.cpp: ScratchpadFrame implementation
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

#include "ComposerFrame.h"
#include "GyreEnv.h"
#include "ScratchpadFrame.h"

namespace gyreide {

void ScratchpadFrame::clear() { scratchText->setText(""); }

void ScratchpadFrame::del() {}

void ScratchpadFrame::load() {
  loadFileName = QFileDialog::getOpenFileName(
      this, tr("Load File"), tabBar->userInfo()->userdir(), tr("File (*)"));

  QFile f(loadFileName);
  if (f.open(QFile::ReadOnly | QFile::Text)) {
    QTextStream in(&f);
    scratchText->setText(in.readAll());
    f.close();
  }

  saveFileName = loadFileName;
}

void ScratchpadFrame::append() {
  loadFileName = QFileDialog::getOpenFileName(
      this, tr("Load File"), tabBar->userInfo()->userdir(), tr("File (*)"));

  QFile f(loadFileName);
  if (f.open(QFile::ReadOnly | QFile::Text)) {
    QTextStream in(&f);
    scratchText->setText(scratchText->toPlainText() + "\n" + in.readAll());
    f.close();
  }
}

void ScratchpadFrame::save_as() {
  saveFileName =
      QFileDialog::getSaveFileName(this, tr("Save As"), "", tr("File (*)"));
  save();
}

void ScratchpadFrame::save() {
  QString text = scratchText->toPlainText();

  QSaveFile file(saveFileName);
  file.open(QIODevice::WriteOnly);
  file.write(text.toUtf8());
  file.commit();
}

ScratchpadFrame::ScratchpadFrame(QString name, MainTabBar* tb)
    : name(name), tabBar(tb) {
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

  scratchText = new QTextEdit();
  scratchText->setAlignment(Qt::AlignTop);

  scrollArea = new QScrollArea();
  scrollArea->setWidget(scratchText);
  scrollArea->setWidgetResizable(true);
  scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

  QSizePolicy spScratch(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spScratch.setVerticalStretch(1);
  scratchText->setSizePolicy(spScratch);

  auto layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(toolBar);
  layout->addWidget(scrollArea);

  this->setLayout(layout);
}

}  // namespace gyreide
