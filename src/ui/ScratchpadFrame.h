/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  ScratchpadFrame.h: ScratchpadFrame class
 **
 **/
#ifndef _GYREUI_SRC_UI_SCRATCHPADFRAME_H_
#define _GYREUI_SRC_UI_SCRATCHPADFRAME_H_

#include <QFrame>
#include <QLabel>
#include <QTextEdit>
#include <QToolBar>
#include <QWidget>

#include "ComposerFrame.h"
#include "GyreEnv.h"
#include "MainTabBar.h"

QT_BEGIN_NAMESPACE
class QDate;
class QLabel;
class QScrollArea;
class QTextEdit;
class QToolBar;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace gyreui {

class ComposerFrame;
class MainTabBar;
class MainWindow;

class ScratchpadFrame : public QFrame {
  Q_OBJECT

 public:
  explicit ScratchpadFrame(QString, MainTabBar*);

 private:
  void clear();
  void load();
  void append();
  void save();
  void save_as();
  void del();

  void log(QString msg) { tabBar->log(msg); }

  void setContextStatus(QString str) { tabBar->setContextStatus(str); }

  void showEvent(QShowEvent* event) override {
    QWidget::showEvent(event);
    tabBar->setContextStatus(name);
  }

  QString loadFileName;
  QString saveFileName;

  QString name;
  QScrollArea* scrollArea;
  QTextEdit* scratchText;
  QToolBar* toolBar;
  MainTabBar* tabBar;
};

}  // namespace gyreui

#endif /* _GYREUI_SRC_UI_SCRATCHPADFRAME_H_ */
