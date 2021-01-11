/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  EnvironmentView.h: EnvironmentView class
 **
 **/
#ifndef GYREUI_UI_ENVIRONMENTVIEW_H_
#define GYREUI_UI_ENVIRONMENTVIEW_H_

#include <QFrame>
#include <QWidget>

#include "ConsoleFrame.h"
#include "GyreEnv.h"
#include "MainWindow.h"
#include "TtyWidget.h"
#include "user.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace gyreui {

class MainWindow;
class ConsoleFrame;

class EnvironmentView : public QFrame {
  Q_OBJECT

 public:
  explicit EnvironmentView(QString, MainWindow*);
  static const char* configFile;
  static const char* version;

  void log(QString);

  GyreEnv* get_gyre();

 private:
  void setContextStatus(QString);
  void showEvent(QShowEvent*) override;

  MainWindow* mw;
  QString name;
  ConsoleFrame* console;
  QLabel* bannerLabel;
  QVBoxLayout* layout;
};

} /* namespace gyreui */

#endif /* GYREUI_UI_ENVIRONMENTVIEW_H_ */
