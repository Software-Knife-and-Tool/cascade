/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  UserFrame.h: UserFrame class
 **
 **/
#ifndef _GYREUI_SRC_UI_USERFRAME_H_
#define _GYREUI_SRC_UI_USERFRAME_H_

#include <QFrame>
#include <QWidget>

#include "MainTabBar.h"
#include "MainWindow.h"
#include "user.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QWidget;
class QLabel;
QT_END_NAMESPACE

namespace gyreui {

class MainTabBar;

class UserFrame : public QFrame {
  Q_OBJECT

 public:
  explicit UserFrame(QString, MainTabBar*);

 private:
  void log(QString);
  void setContextStatus(QString);
  void showEvent(QShowEvent*) override;

  MainTabBar* tabBar;
  QString name;
  QLabel* bannerLabel;
  QVBoxLayout* layout;
};

}  // namespace gyreui

#endif /* _GYREUI_SRC_UI_USERFRAME_H_ */
