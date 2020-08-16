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
 **  MainTabBar.cpp: MainTabBar class
 **
 **/
#include <QtWidgets>
#include <QTabBar>

#include "CanonFrame.h"
#include "ComposerFrame.h"
#include "ConsoleFrame.h"
#include "InspectorFrame.h"
#include "MainTabBar.h"
#include "MainWindow.h"
#include "ScratchpadFrame.h"
#include "ScriptFrame.h"
#include "ToolFrame.h"

namespace logicaide {

void MainTabBar::log(QString msg) {
  ideFrame->log(msg);
}
  
void MainTabBar::setContextStatus(QString str) {
  mw->setContextStatus(str);
}

User* MainTabBar::userInfo() {
  return mw->userInfo();
}

MainTabBar::MainTabBar(MainWindow *mw) : mw(mw) {
  
  ideFrame = new IdeFrame("ide", this);
    
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  auto canon = new Canon();

#if 0
  if (!QObject::connect(composef, &ComposerFrame::evalHappened,
                        canonf, &CanonFrame::runStatus))
    exit(0);
#endif
  
  add(ideFrame, QString("IDE"));
  log(";;; IDE frame loaded");

  add(new ToolFrame("tools", this, canon), "tools");
  log(";;; tools frame loaded");

  add(new ScriptFrame("script",
                      this,
                      canon,
                      ideFrame->get_canon()),
      "scripts");
  log(";;; scripts frame loaded");

  add(new InspectorFrame("inspect", this, canon), "inspector");
  log(";;; inspector frame loaded");

  add(new UserFrame("user", this), "user");
  log(";;; preferences frame loaded");
}

} /* logicaide namespace */
