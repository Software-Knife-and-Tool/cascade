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
#ifndef GYREUI_UI_INSPECTORFRAME_H_
#define GYREUI_UI_INSPECTORFRAME_H_

#include <QFrame>
#include <QLabel>
#include <QTextEdit>
#include <QToolBar>
#include <QWidget>

#include "ComposerFrame.h"
#include "GyreEnv.h"
#include "MainWindow.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QTextEdit;
class QToolBar;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace gyreui {

class MainWindow;
class MainWindow;

class InspectorFrame : public QFrame {
  Q_OBJECT

 public:
  explicit InspectorFrame(QString, MainWindow*, GyreEnv*);

 private:
  void clear();
  void eval();

  void log(QString msg) { mw->log(msg); }

  void setContextStatus(QString str) { mw->setContextStatus(str); }

  MainWindow* mw;
  GyreEnv* devEnv;
  QString name;
  ComposerFrame* composerFrame;
  ;
  QLabel* viewLabel;
  QLabel* timeLabel;
  QToolBar* toolBar;
};

}  // namespace gyreui

#endif /* GYREUI_UI_INSPECTORFRAME_H_ */
