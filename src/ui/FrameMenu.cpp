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
#include "FrameMenu.h"
#include "MainMenuBar.h"
#include "MainWindow.h"

namespace gyreui {

void FrameMenu::envFrame() {
  mw->setContextStatus("<b>Frame|Env</b>");
  mw->setCentralWidget(this);
}

QWidget* FrameMenu::defaultView() { return ev; }

void FrameMenu::sysFrame() { mw->setContextStatus("<b>Frame|Sys</b>"); }

FrameMenu::FrameMenu(MainMenuBar* mb)
    : mb(mb), mw(mb->mw_()), ev(new EnvironmentView("environment", mw)) {
#if 0
  auto devEnv = new GyreEnv();
  auto uiDev = envView->get_gyre();

  /*
  if (!QObject::connect(composef, &ComposerFrame::evalHappened,
                        canonf, &GyreFrame::runStatus))
    exit(0);
  */

  add(envView, QString("environment"));
  log(";;; environment frame loaded");

  add(new PanelFrame("panels", this, devEnv), "panels");
  log(";;; panels frame loaded");

  add(new ScriptFrame("script", this, devEnv, uiDev), "scripts");
  log(";;; scripts frame loaded");

  add(new UserFrame("user", this), "user");
  log(";;; preferences frame loaded");

#endif
}

} /* namespace gyreui */
