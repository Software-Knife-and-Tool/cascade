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

#include <QtWidgets>
#include <QDateTime>
#include <QMdiArea>

#include "ComposerFrame.h"
#include "LocusFrame.h"
#include "MainMenuBar.h"
#include "MainWindow.h"

namespace locus {

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

  QString message = tr("A context menu is available by right-clicking");
  QLabel *context = new QLabel(message);

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

  locusFrame = new LocusFrame(mdiArea);
  locusFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  locusFrame->showMaximized();
  
  auto lw = mdiArea->addSubWindow(locusFrame);
  lw->setWindowFlags(Qt::FramelessWindowHint);
  lw->showMaximized();

#if 0
  connect(lw,
          &QMdiSubWindow::windowStateChanged,
          [=, &lw]() {
            switch (lw->windowState()) {
            case Qt::WindowMinimized:
            case Qt::WindowMaximized:
            case Qt::WindowFullScreen:
              break;
            case Qt::WindowNoState:
            case Qt::WindowActive:
              lw->showMaximized();
              break;
            default:
              lw->showMinimized();
              break;
            }});
#endif
  
  composerFrame = new ComposerFrame(mdiArea);
  composerFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  composerFrame->showMaximized();
  
  auto cw = mdiArea->addSubWindow(composerFrame);
  cw->setWindowFlags(Qt::FramelessWindowHint);
  cw->showMaximized();

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
    
  setWindowTitle(tr("(logica locus)"));
}

} /* locus namespace */
