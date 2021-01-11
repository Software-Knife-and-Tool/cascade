/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  IdeFrame.h: IdeFrame class
 **
 **/
#ifndef GYREUIFRAME_H_
#define GYREUIFRAME_H_

#include <QFrame>
#include <QWidget>

#include "ConsoleFrame.h"
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

namespace gyreui {

class ViewFrame;
class ConsoleFrame;

class UiFrame : public QFrame {
  Q_OBJECT

 public:
  explicit UiFrame(QString, ViewFrame*);
  static const char* configFile;
  static const char* version;

  void log(QString);

  GyreEnv* get_gyre();

 private:
  void setContextStatus(QString);
  void showEvent(QShowEvent*) override;

  ViewFrame* viewFrame;
  QString name;
  ConsoleFrame* console;
  QLabel* bannerLabel;
  QVBoxLayout* layout;
};

}  // namespace gyreui

#endif /* GYREUIFRAME_H_ */
