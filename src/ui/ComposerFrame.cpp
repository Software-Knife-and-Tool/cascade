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
 **  ComposerFrame.cpp: ComposerFrame implementation
 **
 **/
#include <QFileDialog>
#include <QLabel>
#include <QSplitter>
#include <QTextEdit>
#include <QToolBar>
#include <QString>
#include <QtWidgets>

#include "ComposerFrame.h"
#include "canon.h"

namespace logicaide {

void ComposerFrame::clear() {
  editText->setText("");
  evalText->setText("");
}

void ComposerFrame::load() {
  loadFileName =
    QFileDialog::getOpenFileName(this,
                                 tr("Load File"),
                                 tabBar->userInfo()->userdir(),
                                 tr("File (*)"));

  QFile f(loadFileName);
  if (f.open(QFile::ReadOnly | QFile::Text)) {
    QTextStream in(&f);
    editText->setText(in.readAll());
    f.close();
  }

  saveFileName = loadFileName;
}
    
void ComposerFrame::eval() {
  QString out;

  tabBar->setContextStatus(tr("eval"));
  
  auto error =
    canon->withException([this, &out]() {
         out = canon->rep(editText->toPlainText());
       });

  evalText->setText(out + error);

  emit evalHappened(editText->toPlainText());
}

void ComposerFrame::reset() {
  canon = new Canon();
}

void ComposerFrame::del() {
}

void ComposerFrame::save_as() {
  saveFileName = QFileDialog::getSaveFileName(this,
        tr("Save As"), "",
        tr("File (*)"));
  save();
}

void ComposerFrame::save() {
  QString text = editText->toPlainText();
  
  QSaveFile file(saveFileName);
  file.open(QIODevice::WriteOnly);
  file.write(text.toUtf8());
  file.commit();
}

bool ComposerFrame::eventFilter(QObject *watched, QEvent *event) {
  if ( /* watched == textEdit && */ event->type() == QEvent::KeyPress) {
    QKeyEvent *e = static_cast < QKeyEvent * >(event);
    if (e->key() == Qt::Key_Return &&
        e->modifiers() & Qt::ShiftModifier) {
      eval();
      return true;
    }
  }
    
  return tabBar->get_mw()->eventFilter(watched, event);
}
  
ComposerFrame::ComposerFrame(QString name, MainTabBar* tb, Canon* cn)
  : tabBar(tb), canon(cn), name(name) {
  
  auto size = this->frameSize();

  toolBar = new QToolBar();
  connect(toolBar->addAction(tr("clear")),
          &QAction::triggered, this, &ComposerFrame::clear);
  connect(toolBar->addAction(tr("load")),
          &QAction::triggered, this, &ComposerFrame::load);
  connect(toolBar->addAction(tr("eval")),
          &QAction::triggered, this, &ComposerFrame::eval);
  connect(toolBar->addAction(tr("reset")),
          &QAction::triggered, this, &ComposerFrame::reset);
  connect(toolBar->addAction(tr("save")),
          &QAction::triggered, this, &ComposerFrame::save);
  connect(toolBar->addAction(tr("save as")),
          &QAction::triggered, this, &ComposerFrame::save_as);
  connect(toolBar->addAction(tr("del")),
          &QAction::triggered, this, &ComposerFrame::del);

  editText = new QTextEdit();
  editScroll = new QScrollArea();
  editScroll->setWidget(editText);
  editScroll->setWidgetResizable(true);
  editScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  editScroll->installEventFilter(this);

  evalText = new QLabel();
  evalScroll = new QScrollArea();
  evalScroll->setWidget(evalText);
  evalScroll->setWidgetResizable(true);
  evalScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  evalScroll->installEventFilter(this);
  evalScroll->setMinimumHeight(size.height() / 2);
  
  QSizePolicy spEdit(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spEdit.setVerticalStretch(1);
  editText->setSizePolicy(spEdit);

  QSizePolicy spEval(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spEval.setVerticalStretch(1);
  evalText->setSizePolicy(spEval);

  auto vs = new QSplitter(Qt::Vertical, this);
  vs->addWidget(editScroll);
  vs->addWidget(evalScroll);

  auto layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(toolBar);
  layout->addWidget(vs);
  
  setLayout(layout);
}

} /* logicaide namespace */
