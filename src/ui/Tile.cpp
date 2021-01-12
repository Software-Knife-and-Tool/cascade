/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  TileFrame.cpp: TileFrame implementation
 **
 **/
#include <QFileDialog>
#include <QLabel>
#include <QSplitter>
#include <QString>
#include <QTextEdit>
#include <QToolBar>
#include <QtWidgets>

#include "Tile.h"

namespace gyreui {

namespace {

void scrub_layout(QLayout* layout) {
  QLayoutItem* item;
  QLayout* sublayout;
  QWidget* widget;

  while ((item = layout->takeAt(0))) {
    if ((sublayout = item->layout()) != 0) { /* do the same for sublayout*/
    } else if ((widget = item->widget()) != 0) {
      widget->hide();
      delete widget;
    } else {
      delete item;
    }
  }

  delete layout;
}

}  // namespace

void Tile::log(QString msg) { mw->log(msg); }

void Tile::split(QFrame* fr) {
  switch (splitState) {
    case UNSPLIT:
      break;
    case HORIZONTAL:
      splitTile = new Tile(mw, fr);
      splith();
      break;
    case VERTICAL:
      splitTile = new Tile(mw, fr);
      splitv();
      break;
  }
}

void Tile::rebase(QFrame* base) {
  auto size = this->frameSize();

  baseFrame = base;
  baseFrame->setMinimumHeight(size.height() / 2);

  QSizePolicy spBase(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spBase.setVerticalStretch(1);
  baseFrame->setSizePolicy(spBase);

  auto layout = new QVBoxLayout();
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(baseFrame);
  layout->setSizeConstraint(QLayout::SetMinimumSize);

  scrub_layout(this->layout());
  setLayout(layout);

  setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Tile::splitv() {
  auto size = this->frameSize();

  splitState = VERTICAL;

  auto panel = (splitTile == nullptr) ? new QFrame() : splitTile;
  panel->setMinimumHeight(size.height() / 2);

  QSizePolicy spPanel(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spPanel.setVerticalStretch(1);
  panel->setSizePolicy(spPanel);

  auto vs = new QSplitter(Qt::Vertical, this);
  vs->addWidget(baseFrame);
  vs->addWidget(panel);
  vs->setStretchFactor(1, 1);

  auto layout = new QVBoxLayout();
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(vs);
  layout->setSizeConstraint(QLayout::SetMinimumSize);

  scrub_layout(this->layout());
  setLayout(layout);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Tile::splith() {
  auto size = this->frameSize();

  splitState = HORIZONTAL;

  auto panel = (splitTile == nullptr) ? new QFrame() : splitTile;
  panel->setMinimumWidth(size.width() / 2);

  QSizePolicy spPanel(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spPanel.setHorizontalStretch(1);
  panel->setSizePolicy(spPanel);

  auto hs = new QSplitter(Qt::Horizontal, this);
  hs->addWidget(baseFrame);
  hs->addWidget(panel);
  hs->setStretchFactor(1, 1);

  auto layout = new QVBoxLayout();
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(hs);
  layout->setSizeConstraint(QLayout::SetMinimumSize);

  scrub_layout(this->layout());
  setLayout(layout);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

Tile::Tile(MainWindow* tb, QFrame* cf) : mw(tb), baseFrame(cf) {
  splitState = UNSPLIT;
  splitTile = nullptr;

  baseFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

  QSizePolicy spBase(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spBase.setVerticalStretch(1);
  baseFrame->setSizePolicy(spBase);

  auto layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(baseFrame);

  setLayout(layout);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

}  // namespace gyreui
