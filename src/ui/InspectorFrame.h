/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  InspectorFrame.h: InspectorFrame class
 **
 **/
#ifndef _GYREIDE_SRC_UI_INSPECTORFRAME_H_
#define _GYREIDE_SRC_UI_INSPECTORFRAME_H_

#include <QFrame>
#include <QLabel>
#include <QTextEdit>
#include <QToolBar>
#include <QWidget>

#include "GyreEnv.h"
#include "ComposerFrame.h"
#include "MainTabBar.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QTextEdit;
class QToolBar;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace gyreide {

class MainTabBar;
class MainWindow;
  
class InspectorFrame : public QFrame {

 Q_OBJECT

 public:
  explicit InspectorFrame(QString, MainTabBar*, GyreEnv*);

 private:
  void clear();
  void eval();

  void log(QString msg) { tabBar->log(msg); }
  
  void setContextStatus(QString str) {
    tabBar->setContextStatus(str);
  }

  MainTabBar *tabBar;
  GyreEnv* devEnv;
  QString name;
  ComposerFrame* composerFrame;;
  QLabel* viewLabel;
  QLabel* timeLabel;
  QToolBar* toolBar;  
};

} /* gyreide namespace */

#endif  /* _GYREIDE_SRC_UI_INSPECTORFRAME_H_ */
