#ifndef _LOCUS_SRC_LOCUS_MAINWINDOW_H_
#define _LOCUS_SRC_LOCUS_MAINWINDOW_H_

#include <QMainWindow>
#include <QStatusBar>
#include <QTimer>
#include <QDateTime>

#include "StatusClock.h"
#include "LocusFrame.h"
#include "MainMenuBar.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QDateTime;
class QStatusBar;
QT_END_NAMESPACE

namespace locus {

class MainWindow : public QMainWindow {

  Q_OBJECT

 public:
  MainWindow();

  void setContextStatus(const char* str) {

    statusBar()->showMessage(tr(str));
  }

 protected:
  // void contextMenuEvent(QContextMenuEvent *event) override;

 private:
  void createStatusBar();

 private:
  QDateTime startTime;
  StatusClock* statusClock;
  LocusFrame* locusFrame;
  // MainMenuBar* mainMenuBar;
  QLabel *infoLabel;  
};

} /* locus namespace */

#endif  /* _LOCUS_SRC_LOCUS_MAINWINDOW_H_ */
