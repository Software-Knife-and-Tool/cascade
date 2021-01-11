/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  MainWindow.h: MainWindow class
 **
 **/
#ifndef GYREUI_UI_MAINWINDOW_H_
#define GYREUI_UI_MAINWINDOW_H_

#include <QDateTime>
#include <QMainWindow>
#include <QMdiArea>
#include <QStatusBar>
#include <QTimer>

#include "MainMenuBar.h"
#include "StatusClock.h"
#include "mu.h"
#include "user.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QDateTime;
class QLabel;
class QStatusBar;
QT_END_NAMESPACE

namespace gyreui {

class MainMenuBar;
class EnvironmentView;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow();

  MainMenuBar* mainMenuBar() { return this->menuBar; }
  User* userInfo() { return this->user; }

  void log(QString);
  void setContextStatus(QString);

 private:
  //  void showEvent(QShowEvent*) override;

 protected:
  void contextMenuEvent(QContextMenuEvent* event) override;

 private:
  void createStatusBar();

 private:
  EnvironmentView* env;
  User* user;
  QLabel* contextLabel;
  MainMenuBar* menuBar;
  QDateTime startTime;
  StatusClock* statusClock;
};

} /* namespace gyreui */

#endif /* GYREUI_UI_MAINWINDOW_H_ */
