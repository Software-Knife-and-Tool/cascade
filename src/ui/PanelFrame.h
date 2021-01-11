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
#ifndef GYREUI_UI_PANELFRAME_H_
#define GYREUI_UI_PANELFRAME_H_

#include <QFrame>
#include <QLabel>
#include <QTextEdit>
#include <QToolBar>
#include <QWidget>

#include "GyreEnv.h"
#include "Tile.h"
#include "ViewFrame.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QTextEdit;
class QToolBar;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace gyreui {

class ViewFrame;
class MainWindow;

class PanelFrame : public QFrame {
  Q_OBJECT

 public:
  explicit PanelFrame(QString, ViewFrame*, GyreEnv*);

 private:
  void showEvent(QShowEvent* event) {
    QWidget::showEvent(event);
    viewFrame->setContextStatus(name);
  }

  void log(QString msg) { viewFrame->log(msg); }

  QToolButton* toolMenu();

  ViewFrame* viewFrame;
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

#endif /* GYREUI_UI_PANELFRAME_H_ */
