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
 **  MainWindow.cpp: MainWindow implementation
 **
 **/
#include <QDateTime>
#include <QtGui>
#include <QtWidgets>

#include "ComposerFrame.h"
#include "ConsoleFrame.h"
#include "MainMenuBar.h"
#include "MainTabBar.h"
#include "MainWindow.h"
#include "user.h"

namespace logicaide {

void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
  QMenu menu(this);
  
  menu.addAction(menuBar->cutAct);
  menu.addAction(menuBar->copyAct);
  menu.addAction(menuBar->pasteAct);
  menu.exec(event->globalPos());
}

void MainWindow::setContextStatus(QString str) {
  contextLabel->setText(str);
}

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
  tabBar = new MainTabBar(this);

  setMenuBar(menuBar->menu_bar());
  setCentralWidget(tabBar);
  createStatusBar();
  
  resize(QDesktopWidget().availableGeometry(this).size() * 0.8);
  setWindowTitle(tr("Software Knife and Tool Logica IDE"));
}

} /* logicaide namespace */
