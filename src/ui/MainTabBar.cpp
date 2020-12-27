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

namespace gyreide {

void MainTabBar::log(QString msg) { ideFrame->log(msg); }

void MainTabBar::setContextStatus(QString str) { mw->setContextStatus(str); }

User* MainTabBar::userInfo() { return mw->userInfo(); }

MainTabBar::MainTabBar(MainWindow* mw) : mw(mw) {
  ideFrame = new IdeFrame("ide", this);

  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  auto devEnv = new GyreEnv();
  auto ideDev = ideFrame->get_gyre();

#if 0
  if (!QObject::connect(composef, &ComposerFrame::evalHappened,
                        canonf, &GyreFrame::runStatus))
    exit(0);
#endif

  add(ideFrame, QString("IDE"));
  log(";;; IDE frame loaded");

  add(new PanelFrame("panels", this, devEnv), "panels");
  log(";;; tools frame loaded");

  add(new ScriptFrame("script", this, devEnv, ideDev), "scripts");
  log(";;; scripts frame loaded");

  add(new UserFrame("user", this), "user");
  log(";;; preferences frame loaded");
}

}  // namespace gyreide
