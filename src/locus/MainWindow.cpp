#include <QtWidgets>
#include <QDateTime>

#include "MainMenuBar.h"
#include "MainWindow.h"
#include "LocusFrame.h"

namespace locus {

MainWindow::MainWindow() {

  createStatusBar();

  MainMenuBar *mainMenuBar = new MainMenuBar(this);
  
  locusFrame = new LocusFrame();
  setCentralWidget(locusFrame);
  
  setWindowTitle(tr("Logica Locus"));
  setMinimumSize(160, 160);
  resize(480, 320);
}

#if 0
void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
  
  QMenu menu(this);
  menu.addAction(cutAct);
  menu.addAction(copyAct);
  menu.addAction(pasteAct);
  menu.exec(event->globalPos());
}
#endif
  
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
