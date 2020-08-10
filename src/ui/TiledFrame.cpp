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
 **  TiledFrame.cpp: TiledFrame implementation
 **
 **/
#include <QFileDialog>
#include <QLabel>
#include <QTextEdit>
#include <QToolBar>
#include <QString>
#include <QtWidgets>

#include "TiledFrame.h"
#include "canon.h"

namespace composer {

void TiledFrame::splitv() {

}

void TiledFrame::splith() {

}
  
void TiledFrame::tile() {
  saveFileName = QFileDialog::getSaveFileName(this,
        tr("Save As"), "",
        tr("File (*)"));
}

TiledFrame::TiledFrame(MainTabBar* tb, Canon* cn)
  : tabBar(tb),
    canon(cn),
    edit_text(new QTextEdit()),
    eval_text(new QLabel()),
    tool_bar(new QToolBar()) {

  connect(tool_bar->addAction(tr("split-v")),
          &QAction::triggered, this, &TiledFrame::splitv);
  connect(tool_bar->addAction(tr("split-h")),
          &QAction::triggered, this, &TiledFrame::splith);
  connect(tool_bar->addAction(tr("new")),
          &QAction::triggered, this, &TiledFrame::tile);

  edit_text->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  edit_text->setStyleSheet(style);
  
  eval_text->setAlignment(Qt::AlignTop);
  eval_text->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  eval_text->setStyleSheet(style);

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

} /* composer namespace */
