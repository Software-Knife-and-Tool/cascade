/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  FrameMenu.cpp: FrameMenu class
 **
 **/
#include <QtWidgets>

#include "EnvironmentView.h"
#include "FileView.h"
#include "MainMenuBar.h"
#include "MainWindow.h"
#include "SystemView.h"

namespace gyreui {

void FrameMenu::envFrame() {
  mw->setContextStatus("<b>Frame|Env</b>");
  mw->setCentralWidget(ev);
}

void FrameMenu::sysFrame() {
  mw->setContextStatus("<b>Frame|Sys</b>");
  mw->setCentralWidget(sv);
}

QWidget* FrameMenu::defaultView() { return ev; }

FrameMenu::FrameMenu(MainMenuBar* mb) : mb(mb) {

  mw = mb->mw;
    
  auto devEnv = new GyreEnv();

  ev = new EnvironmentView("environment", mw);
  sv = new SystemView("system", mw, devEnv);
  fv = new FileView("file system", mw);

#if 0
  add(new ScriptFrame("script", this, devEnv, uiDev), "scripts");
  log(";;; scripts frame loaded");

  add(new UserFrame("user", this), "user");
  log(";;; preferences frame loaded");
#endif
}

} /* namespace gyreui */
