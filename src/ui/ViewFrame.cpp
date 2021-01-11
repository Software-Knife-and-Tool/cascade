/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  ViewFrame.cpp: ViewFrame class
 **
 **/
#include <QTabBar>
#include <QtWidgets>

#include "ComposerFrame.h"
#include "ConsoleFrame.h"
#include "GyreFrame.h"
#include "InspectorFrame.h"
#include "MainWindow.h"
#include "PanelFrame.h"
#include "ScratchpadFrame.h"
#include "ScriptFrame.h"
#include "UiFrame.h"
#include "ViewFrame.h"

namespace gyreui {

void ViewFrame::log(QString msg) { uiFrame->log(msg); }

void ViewFrame::setContextStatus(QString str) { mw->setContextStatus(str); }

User* ViewFrame::userInfo() { return mw->userInfo(); }

ViewFrame::ViewFrame(MainWindow* mw) : mw(mw) {
  uiFrame = new UiFrame("environment", this);

  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  auto devEnv = new GyreEnv();
  auto uiDev = uiFrame->get_gyre();

#if 0
  if (!QObject::connect(composef, &ComposerFrame::evalHappened,
                        canonf, &GyreFrame::runStatus))
    exit(0);
#endif

  add(uiFrame, QString("environment"));
  log(";;; environment frame loaded");

  add(new PanelFrame("panels", this, devEnv), "panels");
  log(";;; panels frame loaded");

  add(new ScriptFrame("script", this, devEnv, uiDev), "scripts");
  log(";;; scripts frame loaded");

  add(new UserFrame("user", this), "user");
  log(";;; preferences frame loaded");
}

}  // namespace gyreui
