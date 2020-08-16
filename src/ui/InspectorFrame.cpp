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
 **  InspectorFrame.cpp: InspectorFrame implementation
 **
 **/
#include <QFileDialog>
#include <QLabel>
#include <QTextEdit>
#include <QToolBar>
#include <QString>
#include <QtWidgets>

#include "CanonEnv.h"
#include "ComposerFrame.h"
#include "InspectorFrame.h"

namespace logicaide {

void InspectorFrame::clear() {
  //  edit_text->setText("");
}

InspectorFrame::InspectorFrame(QString name,
                               MainTabBar* tb,
                               CanonEnv* ide,
                               CanonEnv* dev )
  : tabBar(tb),  ideEnv(ide), devEnv(dev), name(name) {
  
  composerFrame = new ComposerFrame("inspector", tb, dev);
  viewLabel = new QLabel("view info");
  timeLabel = new QLabel("time info");
  toolBar = new QToolBar();

  auto layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(toolBar);
  layout->addWidget(composerFrame);
  layout->addWidget(timeLabel);
  layout->addWidget(viewLabel);
  
  setLayout(layout);
}

} /* logicaide namespace */
