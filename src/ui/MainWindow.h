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
#ifndef _GYREUI_SRC_UI_MAINWINDOW_H_
#define _GYREUI_SRC_UI_MAINWINDOW_H_

#include <QDateTime>
#include <QMainWindow>
#include <QMdiArea>
#include <QStatusBar>
#include <QTimer>

#include "MainMenuBar.h"
#include "MainTabBar.h"
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
class MainTabBar;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow();

  void setContextStatus(QString);

  MainTabBar* mainTabBar() { return this->tabBar; }
  MainMenuBar* mainMenuBar() { return this->menuBar; }
  User* userInfo() { return this->user; }

 protected:
  void contextMenuEvent(QContextMenuEvent* event) override;

 private:
  void createStatusBar();

 private:
  User* user;
  QLabel* contextLabel;
  MainMenuBar* menuBar;
  MainTabBar* tabBar;
  QDateTime startTime;
  StatusClock* statusClock;
};

}  // namespace gyreui

#endif /* _GYREUI_SRC_UI_MAINWINDOW_H_ */
