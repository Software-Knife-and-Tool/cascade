/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  SystemView.h: SystemView class
 **
 **/
#ifndef GYREUI_UI_SYSTEMVIEW_H_
#define GYREUI_UI_SYSTEMVIEW_H_

#include <QFrame>
#include <QLabel>
#include <QTextEdit>
#include <QToolBar>
#include <QWidget>

#include "GyreEnv.h"
#include "MainWindow.h"
#include "Tile.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QTextEdit;
class QToolBar;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace gyreui {

class MainWindow;

class SystemView : public QFrame {
  Q_OBJECT

 public:
  explicit SystemView(QString, MainWindow*, GyreEnv*);

 private:
  void showEvent(QShowEvent* event) {
    QWidget::showEvent(event);
    mw->setContextStatus(name);
  }

  void log(QString msg) { mw->log(msg); }

  QToolButton* toolMenu();

  MainWindow* mw;
  bool init;
  GyreEnv* devEnv;
  QString name;
  QLayout* layout;
  QToolBar* toolBar;
  QAction* vsplitAction;
  QAction* hsplitAction;
  QMenu* tm;
  Tile* rootTile;
};

} /* namespace gyreui */

#endif /* GYREUI_UI_SYSTEMVIEW_H_ */
