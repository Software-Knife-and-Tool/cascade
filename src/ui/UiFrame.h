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
#ifndef _GYREUI_SRC_UI_UIFRAME_H_
#define _GYREUI_SRC_UI_UIFRAME_H_

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

namespace gyreui {

class MainTabBar;
class ConsoleFrame;

class UiFrame : public QFrame {
  Q_OBJECT

 public:
  explicit UiFrame(QString, MainTabBar*);
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

}  // namespace gyreui

#endif /* _GYREUI_SRC_UI_UIFRAME_H_ */
