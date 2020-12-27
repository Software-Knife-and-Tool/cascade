/*******
 **
 ** Copyright (c) 2017, James M. Putnam
 ** All rights reserved.
 **
 ** Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are met:
 **
 ** 1. Redistributions of source code must retain the above copyright notice,
 **    this list of conditions and the following disclaimer.
 **
 ** 2. Redistributions in binary form must reproduce the above copyright
 **    notice, this list of conditions and the following disclaimer in the
 **    documentation and/or other materials provided with the distribution.
 **
 ** 3. Neither the name of the copyright holder nor the names of its
 **    contributors may be used to endorse or promote products derived from
 **    this software without specific prior written permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 ** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 ** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 ** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 ** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 ** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 ** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 ** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 ** POSSIBILITY OF SUCH DAMAGE.
 **
 *******/

/********
 **
 **  PanelFrame.h: PanelFrame class
 **
 **/
#ifndef _GYREIDE_SRC_UI_PANELFRAME_H_
#define _GYREIDE_SRC_UI_PANELFRAME_H_

#include <QFrame>
#include <QLabel>
#include <QTextEdit>
#include <QToolBar>
#include <QWidget>

#include "GyreEnv.h"
#include "MainTabBar.h"
#include "Tile.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QTextEdit;
class QToolBar;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

namespace gyreide {

class MainTabBar;
class MainWindow;
  
class PanelFrame : public QFrame {

 Q_OBJECT

 public:
  explicit PanelFrame(QString, MainTabBar*, GyreEnv*);

 private:

  void showEvent(QShowEvent* event) {
    QWidget::showEvent(event);
    tabBar->setContextStatus(name);
  }

  void log(QString msg) { tabBar->log(msg); }
  
  QToolButton* toolMenu();
  
  MainTabBar *tabBar;
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

} /* gyreide namespace */

#endif  /* _GYREIDE_SRC_UI_PANELFRAME_H_ */
