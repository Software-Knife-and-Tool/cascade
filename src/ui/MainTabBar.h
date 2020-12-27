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
#ifndef _GYREIDE_SRC_UI_MAINTABBAR_H_
#define _GYREIDE_SRC_UI_MAINTABBAR_H_

#include <QMainWindow>
#include <QTabWidget>

#include "ConsoleFrame.h"
#include "IdeFrame.h"
#include "MainWindow.h"
#include "UserFrame.h"
#include "user.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QTabWidget;
QT_END_NAMESPACE

namespace gyreide {

class MainWindow;
class ConsoleFrame;
class UserFrame;
class IdeFrame;
  
class MainTabBar : public QTabWidget {

 Q_OBJECT

 public:
  explicit MainTabBar(MainWindow*);

  void log(QString);
  void setContextStatus(QString);
  User* userInfo();
  
  void add(QWidget* w, QString label) {
    addTab(w, label);
  }

  MainWindow* get_mw() {
    return this->mw;
  }

 private slots:

 private:
  MainWindow* mw;
  IdeFrame* ideFrame;
};

} /* loigicaide namespace */

#endif  /* _GYREIDE_SRC_UI_MAINTABBAR_H_ */
