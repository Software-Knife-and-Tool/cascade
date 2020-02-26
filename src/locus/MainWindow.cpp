#include <QtWidgets>
#include <QDateTime>

#include "MainWindow.h"
#include "LocusFrame.h"
#include "MainMenuBar.h"

namespace locus {

MainWindow::MainWindow() {

  createStatusBar();

  mainMenuBar = new MainMenuBar(this);
  
  locusFrame = new LocusFrame();
  setCentralWidget(locusFrame);
  
  setWindowTitle(tr("(locus 'logica)"));
  setMinimumSize(160, 160);
  resize(480, 320);
}

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

} /* locus namespace */
