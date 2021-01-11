/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  MainWindow.cpp: MainWindow implementation
 **
 **/
#include <QDateTime>
#include <QtGui>
#include <QtWidgets>

#include "ComposerFrame.h"
#include "ConsoleFrame.h"
#include "MainMenuBar.h"
#include "MainWindow.h"
#include "ViewFrame.h"
#include "user.h"

namespace gyreui {

void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
  QMenu menu(this);

  // menu.addAction(menuBar->cutAct);
  // menu.addAction(menuBar->copyAct);
  // menu.addAction(menuBar->pasteAct);
  menu.exec(event->globalPos());
}

void MainWindow::setContextStatus(QString str) { contextLabel->setText(str); }

void MainWindow::createStatusBar() {
  startTime = QDateTime::currentDateTime();

  auto dateLabel = new QLabel(startTime.toString("ddd MMMM d yy h:m ap"));
  auto userLabel = new QLabel(" " + user->logname());

  contextLabel = new QLabel("");
  statusClock = new StatusClock(statusBar(), dateLabel);

  QSizePolicy user_sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
  user_sp.setHorizontalStretch(1);
  userLabel->setSizePolicy(user_sp);
  userLabel->setAlignment(Qt::AlignLeft);

  QSizePolicy context_sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
  context_sp.setHorizontalStretch(3);
  contextLabel->setSizePolicy(context_sp);
  contextLabel->setAlignment(Qt::AlignCenter);

  QSizePolicy date_sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
  date_sp.setHorizontalStretch(1);
  dateLabel->setSizePolicy(date_sp);
  dateLabel->setAlignment(Qt::AlignRight);

  statusBar()->addPermanentWidget(dateLabel);
  statusBar()->addWidget(userLabel);
  statusBar()->addWidget(contextLabel);
}

MainWindow::MainWindow() : user(new User()) {
  menuBar = new MainMenuBar(this);
  viewFrame = new ViewFrame(this);

  setMenuBar(menuBar->menu_bar());
  setCentralWidget(viewFrame);
  createStatusBar();

  resize(QDesktopWidget().availableGeometry(this).size() * 0.8);
  setWindowTitle(tr("Software Knife and Tool Gyre UI"));
}

} /* namespace gyreui */
