/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  UserFrame.h: UserFrame class
 **
 **/
#ifndef GYREUI_UI_USERFRAME_H_
#define GYREUI_UI_USERFRAME_H_

#include <QFrame>
#include <QWidget>

#include "MainWindow.h"
#include "ViewFrame.h"
#include "user.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QWidget;
class QLabel;
QT_END_NAMESPACE

namespace gyreui {

class ViewFrame;

class UserFrame : public QFrame {
  Q_OBJECT

 public:
  explicit UserFrame(QString, ViewFrame*);

 private:
  void log(QString);
  void setContextStatus(QString);
  void showEvent(QShowEvent*) override;

  ViewFrame* viewFrame;
  QString name;
  QLabel* bannerLabel;
  QVBoxLayout* layout;
};

}  // namespace gyreui

#endif /* GYREUI_UI_USERFRAME_H_ */
