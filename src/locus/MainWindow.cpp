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
  locusFrame = new LocusFrame(this);
  locusFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  
  mdiArea = new QMdiArea(this);
  mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  mdiArea->setViewMode(QMdiArea::TabbedView);
  mdiArea->setTabPosition(QTabWidget::North);
  mdiArea->addSubWindow(locusFrame);
  
  setCentralWidget(mdiArea);

  createStatusBar();
    
  setWindowTitle(tr("(logica locus)"));
  setMinimumSize(160, 160);
  resize(480, 320);
}

} /* locus namespace */
