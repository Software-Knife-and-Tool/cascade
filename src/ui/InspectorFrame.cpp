/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

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

#include "GyreEnv.h"
#include "ComposerFrame.h"
#include "InspectorFrame.h"

namespace gyreide {

void InspectorFrame::clear() {
  //  edit_text->setText("");
}

InspectorFrame::InspectorFrame(QString name,
                               MainTabBar* tb,
                               GyreEnv* env)
  : tabBar(tb), devEnv(env), name(name) {
  
  composerFrame = new ComposerFrame("inspector", tb, env);
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

} /* gyreide namespace */
