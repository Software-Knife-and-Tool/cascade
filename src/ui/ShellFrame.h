/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  ShellFrame.h: ShellFrame class
 **
 **/
#ifndef _GYREIDE_SRC_UI_SHELLFRAME_H_
#define _GYREIDE_SRC_UI_SHELLFRAME_H_

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
  
class ShellFrame : public QFrame {

 Q_OBJECT

 public:
  explicit ShellFrame(QString, MainTabBar*);

  void log(QString msg) {
    ttyWidget->writeTty(msg);
  }
  
  void setContextStatus(QString);

  void showEvent(QShowEvent*) override;

 protected:

 private:
  MainTabBar* tabBar;
  QString name;
  TtyWidget* ttyWidget;
  QVBoxLayout* layout;
};

} /* gyreide namespace */

#endif  /* _GYREIDE_SRC_UI_SHELLFRAME_H_ */
