/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  MainTabBar.cpp: MainTabBar class
 **
 **/
#include <QTabBar>
#include <QtWidgets>

#include "ComposerFrame.h"
#include "ConsoleFrame.h"
#include "GyreFrame.h"
#include "InspectorFrame.h"
#include "MainTabBar.h"
#include "MainWindow.h"
#include "PanelFrame.h"
#include "ScratchpadFrame.h"
#include "ScriptFrame.h"
#include "UiFrame.h"

namespace gyreui {

void MainTabBar::log(QString msg) { uiFrame->log(msg); }

void MainTabBar::setContextStatus(QString str) { mw->setContextStatus(str); }

User* MainTabBar::userInfo() { return mw->userInfo(); }

MainTabBar::MainTabBar(MainWindow* mw) : mw(mw) {
  uiFrame = new UiFrame("ui", this);

  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  auto devEnv = new GyreEnv();
  auto uiDev = uiFrame->get_gyre();

#if 0
  if (!QObject::connect(composef, &ComposerFrame::evalHappened,
                        canonf, &GyreFrame::runStatus))
    exit(0);
#endif

  add(uiFrame, QString("UI"));
  log(";;; UI frame loaded");

  add(new PanelFrame("panels", this, devEnv), "panels");
  log(";;; tools frame loaded");

  add(new ScriptFrame("script", this, devEnv, uiDev), "scripts");
  log(";;; scripts frame loaded");

  add(new UserFrame("user", this), "user");
  log(";;; preferences frame loaded");
}

}  // namespace gyreui
