/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  PanelFrame.h: PanelFrame class
 **
 **/
#ifndef _GYREUI_SRC_UI_PANELFRAME_H_
#define _GYREUI_SRC_UI_PANELFRAME_H_

#include <QFrame>
#include <QLabel>
#include <QTextEdit>
#include <QToolBar>
#include <QWidget>

#include "GyreEnv.h"
#include "MainTabBar.h"
#include "Tile.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QTextEdit;
class QToolBar;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace gyreui {

class MainTabBar;
class MainWindow;

class PanelFrame : public QFrame {
  Q_OBJECT

 public:
  explicit PanelFrame(QString, MainTabBar*, GyreEnv*);

 private:
  void showEvent(QShowEvent* event) {
    QWidget::showEvent(event);
    tabBar->setContextStatus(name);
  }

  void log(QString msg) { tabBar->log(msg); }

  QToolButton* toolMenu();

  MainTabBar* tabBar;
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

}  // namespace gyreui

#endif /* _GYREUI_SRC_UI_PANELFRAME_H_ */
