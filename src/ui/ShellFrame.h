/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  ShellFrame.h: ShellFrame class
 **
 **/
#ifndef GYREUI_UI_SHELLFRAME_H_
#define GYREUI_UI_SHELLFRAME_H_

#include <QFrame>
#include <QWidget>

#include "GyreEnv.h"
#include "MainWindow.h"
#include "TtyWidget.h"
#include "ViewFrame.h"
#include "user.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

class TtyWidget;

namespace gyreui {

class ViewFrame;

class ShellFrame : public QFrame {
  Q_OBJECT

 public:
  explicit ShellFrame(QString, ViewFrame*);

  void log(QString msg) { ttyWidget->writeTty(msg); }

  void setContextStatus(QString);

  void showEvent(QShowEvent*) override;

 protected:
 private:
  ViewFrame* viewFrame;
  QString name;
  TtyWidget* ttyWidget;
  QVBoxLayout* layout;
};

}  // namespace gyreui

#endif /* GYREUI_UI_SHELLFRAME_H_ */
