/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  MainTabBar.h: MainTabBar class
 **
 **/
#ifndef _GYREUI_SRC_UI_MAINTABBAR_H_
#define _GYREUI_SRC_UI_MAINTABBAR_H_

#include <QMainWindow>
#include <QTabWidget>

#include "ConsoleFrame.h"
#include "MainWindow.h"
#include "UiFrame.h"
#include "UserFrame.h"
#include "user.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QTabWidget;
QT_END_NAMESPACE

namespace gyreui {

class MainWindow;
class ConsoleFrame;
class UserFrame;
class UiFrame;

class MainTabBar : public QTabWidget {
  Q_OBJECT

 public:
  explicit MainTabBar(MainWindow*);

  void log(QString);
  void setContextStatus(QString);
  User* userInfo();

  void add(QWidget* w, QString label) { addTab(w, label); }

  MainWindow* mw_() { return this->mw; }

 private slots:

 private:
  MainWindow* mw;
  UiFrame* uiFrame;
};

}  // namespace gyreui

#endif /* _GYREUI_SRC_UI_MAINTABBAR_H_ */
