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
 **  LocusFrame.cpp: LocusFrame implementation
 **
 **/

#include <QtWidgets>

#include "LocusFrame.h"

namespace locus {

LocusFrame::LocusFrame(MainWindow*) {

  mu = new Mu();
    
  QString hostName = QSysInfo::machineHostName();
  QString userName = qgetenv("USER");

  QString system_html =
    QString("<div align=left><p><h1>Locus ") +
    QString("0.0.1") +
    QString("</h1></p>") + QString("<p><h3>Logica ") +
    QString("0.1.0") +
    QString("</h3></p>") +
    QString("<p><h3>Mu ") +
    mu->version() +
    QString("</h3></p>") +
    QString("<h3>") +
    userName +
    QString(" running on ") +
    hostName +
    QString("</h3></div");
    
  bannerLabel = new QLabel(system_html);
  bannerLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  bannerLabel->setAlignment(Qt::AlignCenter);
  
  consoleWidget = new ConsoleWidget(this, mu);
  
  layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(bannerLabel);
  layout->addWidget(consoleWidget);
  this->setLayout(layout);

  this->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
}

} /* locus namespace */
