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
#ifndef GYREUI_UI_SCRATCHPADFRAME_H_
#define GYREUI_UI_SCRATCHPADFRAME_H_

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

class ScratchpadFrame : public QFrame {
  Q_OBJECT

 public:
  explicit ScratchpadFrame(QString, MainWindow*);

 private:
  void clear();
  void load();
  void append();
  void save();
  void save_as();
  void del();

  void log(QString msg) { mw->log(msg); }

  void setContextStatus(QString str) { mw->setContextStatus(str); }

  void showEvent(QShowEvent* event) override {
    QWidget::showEvent(event);
    mw->setContextStatus(name);
  }

  QString loadFileName;
  QString saveFileName;

  QString name;
  QScrollArea* scrollArea;
  QTextEdit* scratchText;
  QToolBar* toolBar;
  MainWindow* mw;
};

}  // namespace gyreui

#endif /* GYREUI_UI_SCRATCHPADFRAME_H_ */
