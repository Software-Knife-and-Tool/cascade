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
 **  TiledFrame.cpp: TiledFrame implementation
 **
 **/
#include <QFileDialog>
#include <QLabel>
#include <QTextEdit>
#include <QToolBar>
#include <QSplitter>
#include <QString>
#include <QtWidgets>

#include "ScratchpadFrame.h"
#include "Tile.h"
#include "TiledFrame.h"
#include "canon.h"

namespace logicaide {

namespace {

void scrub_layout(QLayout* layout) {
  QLayoutItem * item;
  QLayout * sublayout;
  QWidget * widget;
  while ((item = layout->takeAt(0))) {
    if ((sublayout = item->layout()) != 0) {/* do the same for sublayout*/}
    else if ((widget = item->widget()) != 0) {widget->hide(); delete widget;}
    else {delete item;}
  }
  
  delete layout;
}
}

QToolButton* TiledFrame::toolMenu() {
  auto tb = new QToolButton(tool_bar);
  tb->setToolButtonStyle(Qt::ToolButtonTextOnly);
  tb->setText("tools");
  tb->setPopupMode(QToolButton::MenuButtonPopup);
  
  auto tm = new QMenu(tb);
  tb->setMenu(tm);
  tb->setStyleSheet(style);
  
  tm->addAction(tr("&composer"),
                [this] () {
                  if (init)
                    root_tile->rebase(new ComposerFrame("rebase-composer",
                                                       tabBar,
                                                       canon));
                  else
                    root_tile->split(new ComposerFrame("split-composer",
                                                       tabBar,
                                                       canon));
                  init = false;
                });
  
  tm->addAction(tr("&console"),
                [this] () {
                  if (init)
                    root_tile->rebase(new ConsoleFrame("rebase-console",
                                                       tabBar));
                  else
                    root_tile->split(new ConsoleFrame("split-console",
                                                       tabBar));
                  init = false;
                });
  
  // tm->addAction(new QAction(tr("&inspector"), this));
  // tm->addAction(new QAction(tr("&shell"), this));
  
  tm->addAction(tr("&scratch"),
                [this] () {
                  if (init)
                    root_tile->rebase(new ScratchpadFrame("rebase-scratch",
                                                               tabBar));
                  else
                    root_tile->split(new ScratchpadFrame("split-scratch",
                                                         tabBar));
                  init = false;
                });
  return tb;
}

TiledFrame::TiledFrame(QString nm, MainTabBar* tb, Canon* cn)
  : tabBar(tb),
    init(true),    
    canon(cn),
    name(nm),
    layout(new QVBoxLayout()),
    tool_bar(new QToolBar()),
    root_tile(new Tile(tb, new QFrame())) {

  connect(tool_bar->addAction(tr("vsplit")),
          &QAction::triggered, this,
          [this] () { init = false; this->root_tile->splitv(); });

  connect(tool_bar->addAction(tr("hsplit")),
          &QAction::triggered, this,
          [this] () { init = false; this->root_tile->splith(); });
  
  tool_bar->addWidget(toolMenu());

  connect(tool_bar->addAction(tr("del")),
          &QAction::triggered, this, [this] () { });

  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(tool_bar);
  layout->addWidget(root_tile);
  
  setLayout(layout);
  setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  
}

} /* logicaide namespace */
