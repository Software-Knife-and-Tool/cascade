/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  ComposerFrame.h: ComposerFrame class
 **
 **/
#ifndef _GYREUI_SRC_UI_COMPOSERFRAME_H_
#define _GYREUI_SRC_UI_COMPOSERFRAME_H_

#include <QFrame>
#include <QLabel>
#include <QScrollArea>
#include <QTextEdit>
#include <QToolBar>
#include <QWidget>

#include "GyreEnv.h"
#include "MainTabBar.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QScroll;
class QTextEdit;
class QToolBar;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace gyreui {

class MainTabBar;
class MainWindow;

class ComposerFrame : public QFrame {
  Q_OBJECT

 public:
  explicit ComposerFrame(QString, MainTabBar*, GyreEnv*);

 signals:
  void evalHappened(QString);

 private:
  void clear();
  void describe();
  void eval();
  void macroexpand();
  void load();
  void reset();
  void save();
  void save_as();
  void del();

  void setContextStatus(QString str) { tabBar->setContextStatus(str); }

  void showEvent(QShowEvent* event) override {
    QWidget::showEvent(event);
    tabBar->setContextStatus(name);
  }

  bool eventFilter(QObject, QEvent*);
  void log(QString msg) { tabBar->log(msg); }

  bool eventFilter(QObject*, QEvent*) override;

  QString loadFileName;
  QString saveFileName;

  MainTabBar* tabBar;
  GyreEnv* devEnv;
  QString name;
  QTextEdit* editText;
  QLabel* evalText;
  QToolBar* toolBar;
  QScrollArea* editScroll;
  QScrollArea* evalScroll;
};

}  // namespace gyreui

#endif /* _GYREUI_SRC_UI_COMPOSERFRAME_H_ */
