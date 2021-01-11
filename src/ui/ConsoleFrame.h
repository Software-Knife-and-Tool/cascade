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
#ifndef GYREUI_UI_CONSOLEFRAME_H_
#define GYREUI_UI_CONSOLEFRAME_H_

#include <QFrame>
#include <QWidget>

#include "GyreEnv.h"
#include "MainWindow.h"
#include "TtyWidget.h"
#include "user.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

class TtyWidget;

namespace gyreui {

class MainWindow;

class ConsoleFrame : public QFrame {
  Q_OBJECT

 public:
  explicit ConsoleFrame(QString, MainWindow*);

  void log(QString msg) { ttyWidget->writeTty(msg); }

  GyreEnv* get_gyre() { return ttyWidget->get_gyre(); }

 private:
  void setContextStatus(QString);
  void showEvent(QShowEvent*);

  MainWindow* mw;
  QString name;
  TtyWidget* ttyWidget;
  QLabel* bannerLabel;
  QVBoxLayout* layout;
};

}  // namespace gyreui

#endif /* GYREUI_UI_CONSOLEFRAME_H_ */
