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

QToolButton* TiledFrame::toolMenu() {
  auto tb = new QToolButton(toolBar);
  tb->setToolButtonStyle(Qt::ToolButtonTextOnly);
  tb->setText("tools");
  tb->setPopupMode(QToolButton::MenuButtonPopup);
  
  auto tm = new QMenu(tb);
  tb->setMenu(tm);
  
  tm->addAction(tr("&composer"),
                [this] () {
                  if (init)
                    rootTile->rebase(new ComposerFrame("rebase-composer",
                                                       tabBar,
                                                       canon));
                  else
                    rootTile->split(new ComposerFrame("split-composer",
                                                       tabBar,
                                                       canon));
                  init = false;
                });
  
  tm->addAction(tr("&console"),
                [this] () {
                  if (init)
                    rootTile->rebase(new ConsoleFrame("rebase-console",
                                                       tabBar));
                  else
                    rootTile->split(new ConsoleFrame("split-console",
                                                       tabBar));
                  init = false;
                });
  
  // tm->addAction(new QAction(tr("&inspector"), this));
  // tm->addAction(new QAction(tr("&shell"), this));
  
  tm->addAction(tr("&scratch"),
                [this] () {
                  if (init)
                    rootTile->rebase(new ScratchpadFrame("rebase-scratch",
                                                               tabBar));
                  else
                    rootTile->split(new ScratchpadFrame("split-scratch",
                                                         tabBar));
                  init = false;
                });
  return tb;
}

TiledFrame::TiledFrame(QString nm, MainTabBar* tb, Canon* cn)
  : tabBar(tb), canon(cn), name(nm) {

  init = true;

  toolBar = new QToolBar();
    
  connect(toolBar->addAction(tr("vsplit")),
          &QAction::triggered, this,
          [this] () { init = false;
                      rootTile->splitv();
          });

  connect(toolBar->addAction(tr("hsplit")),
          &QAction::triggered, this,
          [this] () { init = false;
                      rootTile->splith();
          });
  
  toolBar->addWidget(toolMenu());

  rootTile = new Tile(tb, new QFrame());
    
  layout = new QVBoxLayout();
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(toolBar);
  layout->addWidget(rootTile);
  
  setLayout(layout);
}

} /* logicaide namespace */
