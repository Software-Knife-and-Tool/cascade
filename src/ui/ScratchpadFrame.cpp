/*******
 **
 ** Copyright (c) 2017, James M. Putnam
 ** All rights reserved.
 **
 ** Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are met:
 **
 ** 1. Redistributions of source code must retain the above copyright notice,
 **    this list of conditions and the following disclaimer.
 **
 ** 2. Redistributions in binary form must reproduce the above copyright
 **    notice, this list of conditions and the following disclaimer in the
 **    documentation and/or other materials provided with the distribution.
 **
 ** 3. Neither the name of the copyright holder nor the names of its
 **    contributors may be used to endorse or promote products derived from
 **    this software without specific prior written permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 ** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 ** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 ** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 ** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 ** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 ** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 ** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 ** POSSIBILITY OF SUCH DAMAGE.
 **
 *******/

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

#include "ScratchpadFrame.h"
#include "ComposerFrame.h"
#include "canon.h"

namespace logicaide {

void ScratchpadFrame::clear() {
  scratchText->setText("");
}

void ScratchpadFrame::load() {
  loadFileName =
    QFileDialog::getOpenFileName(this,
                                 tr("Load File"),
                                 tabBar->userInfo()->userdir(),
                                 tr("File (*)"));

  QFile f(loadFileName);
  if (f.open(QFile::ReadOnly | QFile::Text)) {
    QTextStream in(&f);
    scratchText->setText(in.readAll());
    f.close();
  }

  saveFileName = loadFileName;
}

void ScratchpadFrame::append() {

  loadFileName =
    QFileDialog::getOpenFileName(this,
                                 tr("Load File"),
                                 tabBar->userInfo()->userdir(),
                                 tr("File (*)"));

  QFile f(loadFileName);
  if (f.open(QFile::ReadOnly | QFile::Text)) {
    QTextStream in(&f);
    scratchText->setText(scratchText->toPlainText() + "\n" + in.readAll());
    f.close();
  }
}

void ScratchpadFrame::save_as() {
  saveFileName = QFileDialog::getSaveFileName(this,
        tr("Save As"), "",
        tr("File (*)"));
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
  : name(name),
    scrollArea(new QScrollArea()),
    scratchText(new QTextEdit()),
    toolBar(new QToolBar()),
    tabBar(tb) {

  connect(toolBar->addAction(tr("clear")),
          &QAction::triggered, this, &ScratchpadFrame::clear);
  connect(toolBar->addAction(tr("load")),
          &QAction::triggered, this, &ScratchpadFrame::load);
  connect(toolBar->addAction(tr("append")),
          &QAction::triggered, this, &ScratchpadFrame::append);
  connect(toolBar->addAction(tr("save")),
          &QAction::triggered, this, &ScratchpadFrame::save);
  connect(toolBar->addAction(tr("save as")),
          &QAction::triggered, this, &ScratchpadFrame::save_as);

  scratchText->setAlignment(Qt::AlignTop);
  scratchText->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  scratchText->setStyleSheet(style);

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
  this->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

} /* logicaide namespace */
