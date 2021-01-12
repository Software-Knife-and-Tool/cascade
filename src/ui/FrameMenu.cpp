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
  mw->setCentralWidget(ev);
}

QWidget* FrameMenu::defaultView() { return ev; }

void FrameMenu::sysFrame() { mw->setContextStatus("<b>Frame|Sys</b>"); }

FrameMenu::FrameMenu(MainMenuBar* mb)
    : mb(mb), mw(mb->mw_()), ev(new EnvironmentView("environment", mw)) {}

} /* namespace gyreui */
