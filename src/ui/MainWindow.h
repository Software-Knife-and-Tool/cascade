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
#include "ViewFrame.h"
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
class ViewFrame;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow();

  void setContextStatus(QString);

  MainMenuBar* mainMenuBar() { return this->menuBar; }
  User* userInfo() { return this->user; }
  ViewFrame* viewFrame_() { return this->viewFrame; }

 protected:
  void contextMenuEvent(QContextMenuEvent* event) override;

 private:
  void createStatusBar();

 private:
  User* user;
  QLabel* contextLabel;
  MainMenuBar* menuBar;
  ViewFrame* viewFrame;
  QDateTime startTime;
  StatusClock* statusClock;
};

}  // namespace gyreui

#endif /* GYREUI_UI_MAINWINDOW_H_ */
