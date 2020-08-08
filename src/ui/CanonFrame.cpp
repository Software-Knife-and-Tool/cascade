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
 **  CanonFrame.cpp: CanonFrame implementation
 **
 **/
#include <QFileDialog>
#include <QLabel>
#include <QTextEdit>
#include <QToolBar>
#include <QString>
#include <QtWidgets>

#include "CanonFrame.h"
#include "ComposerFrame.h"
#include "canon.h"

namespace composer {

void CanonFrame::clear() {
  status_text->setText("");
}

void CanonFrame::eval(QString form) {
  QString out;

  tabBar->setContextStatus(tr("eval"));
  
  auto error_text =
    canon->withException([this, form, &out]() {
      out = canon->rep(form.toStdString().c_str());
    });

  status_text->setText(out + error_text);
}

CanonFrame::CanonFrame(MainTabBar* tb, Canon* cn)
  : tabBar(tb),
    canon(cn),
    status_text(new QLabel()) {

  status_text->setAlignment(Qt::AlignTop);
  status_text->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  status_text->setStyleSheet(style);

  QSizePolicy spStatus(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spStatus.setVerticalStretch(1);
  status_text->setSizePolicy(spStatus);

  auto layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(status_text);
  
  this->setLayout(layout);
  this->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QString out;

  auto error_text =
    canon->withException([this, &out]() {
         out = canon->rep("(room :t)");
       });

  status_text->setText(out + error_text);
}

} /* composer namespace */
