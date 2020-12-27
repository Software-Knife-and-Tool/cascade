/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  IdeFrame.h: IdeFrame class
 **
 **/
#ifndef _GYREIDE_SRC_UI_IDEFRAME_H_
#define _GYREIDE_SRC_UI_IDEFRAME_H_

#include <QFrame>
#include <QWidget>

#include "ConsoleFrame.h"
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

namespace gyreide {

class MainTabBar;
class ConsoleFrame;

class IdeFrame : public QFrame {
  Q_OBJECT

 public:
  explicit IdeFrame(QString, MainTabBar*);
  static const char* configFile;
  static const char* version;

  void log(QString);

  GyreEnv* get_gyre();

 private:
  void setContextStatus(QString);
  void showEvent(QShowEvent*) override;

  MainTabBar* tabBar;
  QString name;
  ConsoleFrame* console;
  QLabel* bannerLabel;
  QVBoxLayout* layout;
};

}  // namespace gyreide

#endif /* _GYREIDE_SRC_UI_IDEFRAME_H_ */
