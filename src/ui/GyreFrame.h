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
#ifndef _GYREIDE_SRC_UI_GYREFRAME_H_
#define _GYREIDE_SRC_UI_GYREFRAME_H_

#include <QFrame>
#include <QLabel>
#include <QTextEdit>
#include <QToolBar>
#include <QWidget>

#include "GyreEnv.h"
#include "ComposerFrame.h"
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

namespace gyreide {
  
class ComposerFrame;
class MainTabBar;
class MainWindow;
  
class GyreFrame : public QFrame {

 Q_OBJECT

 public:
  explicit GyreFrame(QString, MainTabBar*, GyreEnv*);

 public slots:
  void runStatus(QString);

 private:
  void del() { }
  void log(QString msg) { tabBar->log(msg); }
  void clear() { statusText->setText(""); }

  void setContextStatus(QString str) {
    tabBar->setContextStatus(str);
  }

  void showEvent(QShowEvent* event) override {
    QWidget::showEvent(event);
    tabBar->setContextStatus(name);
  }

  GyreEnv* devEnv;
  QString name;
  QScrollArea* scrollArea;
  QLabel* statusText;
  MainTabBar* tabBar;
  QDateTime evalDate;
  QToolBar* toolBar;  
};

} /* gyreide namespace */

#endif  /* _GYREIDE_SRC_UI_GYREFRAME_H_ */
