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
 **  TileFrame.cpp: TileFrame implementation
 **
 **/
#include <QFileDialog>
#include <QLabel>
#include <QTextEdit>
#include <QToolBar>
#include <QSplitter>
#include <QString>
#include <QtWidgets>

#include "ComposerFrame.h"
#include "Tile.h"
#include "canon.h"

namespace composer {
  
void Tile::splitv() {

  auto label = new QLabel("top panel");

  QSizePolicy spNew(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spNew.setVerticalStretch(1);
  label->setSizePolicy(spNew);

  auto vsplitter = new QSplitter(Qt::Vertical, this);
  vsplitter->addWidget(label);
  vsplitter->addWidget(this);
  vsplitter->setStretchFactor(1, 1);
 
  auto layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(vsplitter);
  
  this->setLayout(layout);
  this->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Tile::splith() {

  auto label = new QLabel("top panel");

  auto hsplitter = new QSplitter(Qt::Horizontal, this);
  hsplitter->addWidget(label);
  hsplitter->addWidget(this);
  hsplitter->setStretchFactor(1, 1);
 
  auto layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(hsplitter);
  
  this->setLayout(layout);
  this->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

Tile::Tile(MainTabBar* tb, Canon* cn)
  : tabBar(tb),
    canon(cn),
    base_frame(new ComposerFrame(tb, cn)),
    child_tile(nullptr) {

  base_frame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  base_frame->setStyleSheet(style);
  
  QSizePolicy spBase(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spBase.setVerticalStretch(1);
  base_frame->setSizePolicy(spBase);

  auto panel = new QFrame();
  panel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  panel->setStyleSheet(selected);
  
  QSizePolicy spTop(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spTop.setVerticalStretch(1);
  panel->setSizePolicy(spTop);

  auto hsplitter = new QSplitter(Qt::Vertical, this);
  hsplitter->addWidget(base_frame);
  hsplitter->addWidget(panel);
  hsplitter->setStretchFactor(1, 1);
 
  auto layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(hsplitter);
  
  this->setLayout(layout);
  this->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  
}

} /* composer namespace */
