/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  PanelFrame.cpp: PanelFrame implementation
 **
 **/
#include <QFileDialog>
#include <QLabel>
#include <QSplitter>
#include <QString>
#include <QTextEdit>
#include <QToolBar>
#include <QtWidgets>

#include "GyreEnv.h"
#include "InspectorFrame.h"
#include "PanelFrame.h"
#include "ScratchpadFrame.h"
#include "Tile.h"

namespace gyreui {

QToolButton* PanelFrame::toolMenu() {
  auto tb = new QToolButton(toolBar);
  tb->setToolButtonStyle(Qt::ToolButtonTextOnly);
  tb->setText("tools");
  tb->setPopupMode(QToolButton::MenuButtonPopup);

  auto tm = new QMenu(tb);
  tb->setMenu(tm);

  tm->addAction(tr("&composer"), [this]() {
    if (init)
      rootTile->rebase(new ComposerFrame("rebase-composer", tabBar, devEnv));
    else
      rootTile->split(new ComposerFrame("split-composer", tabBar, devEnv));
    init = false;
    vsplitAction->setEnabled(true);
    hsplitAction->setEnabled(true);
  });

  tm->addAction(tr("&console"), [this]() {
    if (init)
      rootTile->rebase(new ConsoleFrame("rebase-console", tabBar));
    else
      rootTile->split(new ConsoleFrame("split-console", tabBar));
    init = false;
    vsplitAction->setEnabled(true);
    hsplitAction->setEnabled(true);
  });

  tm->addAction(tr("&inspector"), [this]() {
    if (init)
      rootTile->rebase(new InspectorFrame("rebase-inspector", tabBar, devEnv));
    else
      rootTile->split(new InspectorFrame("split-inspector", tabBar, devEnv));
    init = false;
    vsplitAction->setEnabled(true);
    hsplitAction->setEnabled(true);
  });

  tm->addAction(tr("&shell"), [this]() {
    if (init)
      rootTile->rebase(new ScratchpadFrame("rebase-shell", tabBar));
    else
      rootTile->split(new ScratchpadFrame("split-shell", tabBar));
    init = false;
    vsplitAction->setEnabled(true);
    hsplitAction->setEnabled(true);
  });

  tm->addAction(tr("&scratch"), [this]() {
    if (init)
      rootTile->rebase(new ScratchpadFrame("rebase-scratch", tabBar));
    else
      rootTile->split(new ScratchpadFrame("split-scratch", tabBar));
    init = false;
    vsplitAction->setEnabled(true);
    hsplitAction->setEnabled(true);
  });
  return tb;
}

PanelFrame::PanelFrame(QString nm, MainTabBar* tb, GyreEnv* dev)
    : tabBar(tb), devEnv(dev), name(nm) {
  init = true;

  toolBar = new QToolBar();

  vsplitAction = toolBar->addAction(tr("vsplit"));
  vsplitAction->setEnabled(false);

  connect(vsplitAction, &QAction::triggered, this,
          [this]() { rootTile->splitv(); });

  hsplitAction = toolBar->addAction(tr("hsplit"));
  hsplitAction->setEnabled(false);

  connect(hsplitAction, &QAction::triggered, this,
          [this]() { rootTile->splith(); });

  toolBar->addWidget(toolMenu());

  rootTile = new Tile(tb, new QFrame());

  layout = new QVBoxLayout();
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(toolBar);
  layout->addWidget(rootTile);

  setLayout(layout);
}

}  // namespace gyreui
