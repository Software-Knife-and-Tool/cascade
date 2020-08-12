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
 **  MainWindow.h: MainWindow class
 **
 **/
#ifndef _LOGICAIDE_SRC_UI_MAINWINDOW_H_
#define _LOGICAIDE_SRC_UI_MAINWINDOW_H_

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

namespace logicaide {

class MainMenuBar;
class MainTabBar;
class ConsoleFrame;
  
class MainWindow : public QMainWindow {

 Q_OBJECT

 public:
  explicit MainWindow();

  void setContextStatus(QString);
  
  MainTabBar* mainTabBar() { return this->tabBar; }
  MainMenuBar* mainMenuBar() { return this->menuBar; }
  User* userInfo() { return this->user; }
  
 protected:
  void contextMenuEvent(QContextMenuEvent *event) override;

 private:
  void createStatusBar();

 private:
  User* user;
  QLabel *contextLabel;
  MainMenuBar* menuBar;
  MainTabBar* tabBar;
  QDateTime startTime;
  StatusClock* statusClock;
};

} /* logicaide namespace */

#endif  /* _LOGICAIDE_SRC_UI_MAINWINDOW_H_ */
