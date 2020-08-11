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
#include <QDate>
#include <QFileDialog>
#include <QLabel>
#include <QScrollArea>
#include <QString>
#include <QTextEdit>
#include <QToolBar>
#include <QtWidgets>

#include "CanonFrame.h"
#include "ComposerFrame.h"
#include "canon.h"

namespace composer {

void CanonFrame::runStatus(QString form) {
  auto date =
    new QString(QDateTime::currentDateTime().toString("ddd MMMM d yy h:m:s ap"));

  statusText->setText(statusText->text() +
                      "\n;;;\n;;; " +
                      form +
                      " evaluated at " +
                      date +
                      "\n;;;\n" +
                      canon->rep("(room :nil)"));
}

  CanonFrame::CanonFrame(QString name, MainTabBar* tb, Canon* cn)
  : canon(cn),
    name(name),
    scrollArea(new QScrollArea()),
    statusText(new QLabel()),
    tabBar(tb) {

  statusText->setAlignment(Qt::AlignTop);
  statusText->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  statusText->setStyleSheet(style);

  scrollArea->setWidget(statusText);
  scrollArea->setWidgetResizable(true);
  scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

  QSizePolicy spStatus(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spStatus.setVerticalStretch(1);
  statusText->setSizePolicy(spStatus);
  
  auto layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(scrollArea);
    
  this->setLayout(layout);
  this->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QString out;

  auto error_text =
    canon->withException([this, &out]() {
         out = canon->rep("(room :default)");
       });

  statusText->setText(out + error_text);
}

} /* composer namespace */
