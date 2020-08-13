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
#include <QTextEdit>
#include <QToolBar>
#include <QString>
#include <QtWidgets>

#include "ComposerFrame.h"
#include "canon.h"

namespace logicaide {

void ComposerFrame::clear() {
  edit_text->setText("");
  eval_text->setText("");
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
    edit_text->setText(in.readAll());
    f.close();
  }

  saveFileName = loadFileName;
}
    
void ComposerFrame::eval() {
  QString out;

  tabBar->setContextStatus(tr("eval"));
  
  auto error_text =
    canon->withException([this, &out]() {
         out = canon->rep(edit_text->toPlainText());
       });

  eval_text->setText(out + error_text);

  emit evalHappened(edit_text->toPlainText());
}

void ComposerFrame::reset() {
  canon = new Canon();
}

void ComposerFrame::save_as() {
  saveFileName = QFileDialog::getSaveFileName(this,
        tr("Save As"), "",
        tr("File (*)"));
  save();
}

void ComposerFrame::save() {
  QString text = edit_text->toPlainText();
  
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
  : tabBar(tb),
    canon(cn),
    name(name),
    edit_text(new QTextEdit()),
    eval_text(new QLabel()),
    tool_bar(new QToolBar()),
    edit_scroll(new QScrollArea()),
    eval_scroll(new QScrollArea()) {

  connect(tool_bar->addAction(tr("clear")),
          &QAction::triggered, this, &ComposerFrame::clear);
  connect(tool_bar->addAction(tr("load")),
          &QAction::triggered, this, &ComposerFrame::load);
  connect(tool_bar->addAction(tr("eval")),
          &QAction::triggered, this, &ComposerFrame::eval);
  connect(tool_bar->addAction(tr("reset")),
          &QAction::triggered, this, &ComposerFrame::reset);
  connect(tool_bar->addAction(tr("save")),
          &QAction::triggered, this, &ComposerFrame::save);
  connect(tool_bar->addAction(tr("save as")),
          &QAction::triggered, this, &ComposerFrame::save_as);

  edit_text->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  edit_text->setStyleSheet(style);
  edit_text->installEventFilter(this);

#if 0
  edit_scroll->setWidget(edit_text);
  edit_scroll->setWidgetResizable(true);
  edit_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
#endif
  
  eval_text->setAlignment(Qt::AlignTop);
  eval_text->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  eval_text->setStyleSheet(style);

#if 0
  eval_scroll->setWidget(eval_text);
  eval_scroll->setWidgetResizable(true);
  eval_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
#endif
  
  QSizePolicy spEdit(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spEdit.setVerticalStretch(1);
  edit_text->setSizePolicy(spEdit);

  QSizePolicy spEval(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spEval.setVerticalStretch(1);
  eval_text->setSizePolicy(spEval);
 
  auto layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(tool_bar);
  layout->addWidget(edit_text);
  layout->addWidget(eval_text);
  
  this->setLayout(layout);
  this->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

} /* logicaide namespace */
