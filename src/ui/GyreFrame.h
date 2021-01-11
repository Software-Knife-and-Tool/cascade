/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  GyreFrame.h: GyreFrame class
 **
 **/
#ifndef GYREUI_UI_GYREFRAME_H_
#define GYREUI_UI_GYREFRAME_H_

#include <QFrame>
#include <QLabel>
#include <QTextEdit>
#include <QToolBar>
#include <QWidget>

#include "ComposerFrame.h"
#include "GyreEnv.h"
#include "MainWindow.h"

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
class MainWindow;
class MainWindow;

class GyreFrame : public QFrame {
  Q_OBJECT

 public:
  explicit GyreFrame(QString, MainWindow*, GyreEnv*);

 public slots:
  void runStatus(QString);

 private:
  void del() {}
  void log(QString msg) { mw->log(msg); }
  void clear() { statusText->setText(""); }

  void setContextStatus(QString str) { mw->setContextStatus(str); }

  void showEvent(QShowEvent* event) override {
    QWidget::showEvent(event);
    mw->setContextStatus(name);
  }

  GyreEnv* devEnv;
  QString name;
  QScrollArea* scrollArea;
  QLabel* statusText;
  MainWindow* mw;
  QDateTime evalDate;
  QToolBar* toolBar;
};

}  // namespace gyreui

#endif /* GYREUI_UI_GYREFRAME_H_ */
