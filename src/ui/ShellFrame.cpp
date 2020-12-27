/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  ShellFrame.cpp: ShellFrame implementation
 **
 **/
#include <QString>
#include <QtWidgets>

#include "ShellFrame.h"

namespace gyreide {

void ShellFrame::setContextStatus(QString str) {
  tabBar->setContextStatus(str);
}

void ShellFrame::showEvent(QShowEvent* event) {
  QWidget::showEvent(event);
  tabBar->setContextStatus(name);
}

ShellFrame::ShellFrame(QString name, MainTabBar* tb) : tabBar(tb), name(name) {
  ttyWidget = new TtyWidget(this);

  QSizePolicy tty_policy = ttyWidget->sizePolicy();
  tty_policy.setVerticalStretch(1);
  ttyWidget->setSizePolicy(tty_policy);

  this->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(ttyWidget);

  setLayout(layout);
}

}  // namespace gyreide
