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
#include <cstdlib>

#include <QDateTime>
#include <QMdiArea>
#include <QtGui>
#include <QtWidgets>

#include "CascadeFrame.h"
#include "ComposerFrame.h"
#include "MainMenuBar.h"
#include "MainWindow.h"

namespace cascade {

void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
  QMenu menu(this);
  
  menu.addAction(mainMenuBar->cutAct);
  menu.addAction(mainMenuBar->copyAct);
  menu.addAction(mainMenuBar->pasteAct);
  menu.exec(event->globalPos());
}

void MainWindow::setContextStatus(const char* str) {
  statusBar()->showMessage(tr(str));
}

void MainWindow::createStatusBar() {
  QString user = tr(std::getenv("LOGNAME"));
  QLabel *context = new QLabel(tr(" ") + user);

  startTime = QDateTime::currentDateTime();
  
  QLabel* dateLabel = new QLabel(startTime.toString("ddd MMMM d yy h:m ap"));
  statusClock = new StatusClock(statusBar(), dateLabel);
  
  statusBar()->addPermanentWidget(dateLabel);  
  statusBar()->addWidget(context);
}

MainWindow::MainWindow() {
  mainMenuBar = new MainMenuBar(this);

  mdiArea = new QMdiArea(this);
  mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  mdiArea->setViewMode(QMdiArea::TabbedView);
  mdiArea->setTabPosition(QTabWidget::North);

  setCentralWidget(mdiArea);

  /* cascade */
  cascadeFrame = new CascadeFrame(mdiArea);
  cascadeFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  // cascadeFrame->showMaximized();

  auto hw = mdiArea->addSubWindow(cascadeFrame);
  hw->setWindowFlags(Qt::FramelessWindowHint);
  hw->setWindowTitle(tr("cascade"));
  hw->showMaximized();
  connect(hw, &QMdiSubWindow::windowStateChanged,
          [=]() {
            cascadeFrame->setVisible(hw->windowState() == Qt::WindowNoState);
          });

  /* composer */
  composerFrame = new ComposerFrame(mdiArea);
  composerFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  // composerFrame->showMaximized();
  
  auto cw = mdiArea->addSubWindow(composerFrame);
  cw->setWindowTitle(tr("composer"));
  cw->setWindowFlags(Qt::FramelessWindowHint);
  cw->setWindowState(Qt::WindowMaximized);
  cw->showMaximized();
  connect(cw, &QMdiSubWindow::windowStateChanged,
          [=]() {
            composerFrame->setVisible(cw->windowState() == Qt::WindowNoState);
          });
#if 0
  /* inspector */
  inFrame = new UiFrame(mdiArea);
  inFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  inFrame->showMaximized();

  auto iw = mdiArea->addSubWindow(inFrame);
  iw->setWindowFlags(Qt::FramelessWindowHint);
  iw->setWindowTitle(tr("inspector"));
  iw->showMaximized();
  connect(iw, &QMdiSubWindow::windowStateChanged,
          [=]() {
            uiFrame->setVisible(iw->windowState() == Qt::WindowNoState);
          });

  /* scripts */
  scFrame = new UiFrame(mdiArea);
  scFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  scFrame->showMaximized();

  auto sw = mdiArea->addSubWindow(scFrame);
  sw->setWindowFlags(Qt::FramelessWindowHint);
  sw->setWindowTitle(tr("scripting"));
  sw->showMaximized();
  connect(sw, &QMdiSubWindow::windowStateChanged,
          [=]() {
            uiFrame->setVisible(sw->windowState() == Qt::WindowNoState);
          });
#endif
  
#if 0
  connect(w,&QMdiSubWindow::windowStateChanged,[=](){
        if(w->windowState() == Qt::WindowNoState){
            mdiArea->removeSubWindow(w);
            if(mdiArea->subWindowList().size() == 0){
                qDebug() << "modify the menu";
            }
        }
    });
#endif

  createStatusBar();
    
  setWindowTitle(tr("Logica Cascade Development Environment"));
}

} /* cascade namespace */
