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
#ifndef GYREUI_UI_COMPOSERFRAME_H_
#define GYREUI_UI_COMPOSERFRAME_H_

#include <QFrame>
#include <QLabel>
#include <QScrollArea>
#include <QTextEdit>
#include <QToolBar>
#include <QWidget>

#include "GyreEnv.h"
#include "ViewFrame.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QScroll;
class QTextEdit;
class QToolBar;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace gyreui {

class ViewFrame;
class MainWindow;

class ComposerFrame : public QFrame {
  Q_OBJECT

 public:
  explicit ComposerFrame(QString, ViewFrame*, GyreEnv*);

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

  void setContextStatus(QString str) { viewFrame->setContextStatus(str); }

  void showEvent(QShowEvent* event) override {
    QWidget::showEvent(event);
    viewFrame->setContextStatus(name);
  }

  bool eventFilter(QObject, QEvent*);
  void log(QString msg) { viewFrame->log(msg); }

  bool eventFilter(QObject*, QEvent*) override;

  QString loadFileName;
  QString saveFileName;

  ViewFrame* viewFrame;
  GyreEnv* devEnv;
  QString name;
  QTextEdit* editText;
  QLabel* evalText;
  QToolBar* toolBar;
  QScrollArea* editScroll;
  QScrollArea* evalScroll;
};

}  // namespace gyreui

#endif /* GYREUI_UI_COMPOSERFRAME_H_ */
