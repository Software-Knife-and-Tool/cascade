/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  ConsoleFrame.h: ConsoleFrame class
 **
 **/
#ifndef _GYREIDE_SRC_UI_CONSOLEFRAME_H_
#define _GYREIDE_SRC_UI_CONSOLEFRAME_H_

#include <QFrame>
#include <QWidget>

#include "GyreEnv.h"
#include "MainTabBar.h"
#include "MainWindow.h"
#include "TtyWidget.h"
#include "user.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

class TtyWidget;

namespace gyreide {

class MainTabBar;
  
class ConsoleFrame : public QFrame {

 Q_OBJECT

 public:
  explicit ConsoleFrame(QString, MainTabBar*);

  void log(QString msg) { ttyWidget->writeTty(msg); }

  GyreEnv* get_gyre() { return ttyWidget->get_gyre(); }
  
private:
  void setContextStatus(QString);
  void showEvent(QShowEvent*);

  MainTabBar* tabBar;
  QString name;
  TtyWidget* ttyWidget;
  QLabel* bannerLabel;
  QVBoxLayout* layout;
};

} /* gyreide namespace */

#endif  /* _GYREIDE_SRC_UI_CONSOLEFRAME_H_ */
