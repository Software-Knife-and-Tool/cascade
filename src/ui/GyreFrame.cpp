/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  GyreFrame.cpp: GyreFrame implementation
 **
 **/
#include <QDate>
#include <QFileDialog>
#include <QLabel>
#include <QScrollArea>
#include <QString>
#include <QTextEdit>
#include <QToolBar>
#include <QtWidgets>

#include "ComposerFrame.h"
#include "GyreEnv.h"
#include "GyreFrame.h"

namespace gyreide {

void GyreFrame::runStatus(QString form) {
  auto date = new QString(
      QDateTime::currentDateTime().toString("ddd MMMM d yy h:m:s ap"));

  statusText->setText(statusText->text() + "\n;;;\n;;; " + form +
                      " evaluated at " + date + "\n;;;\n" +
                      devEnv->rep("(room :nil)"));
}

GyreFrame::GyreFrame(QString name, MainTabBar* tb, GyreEnv* cn)
    : devEnv(cn), name(name), tabBar(tb) {
  toolBar = new QToolBar();
  connect(toolBar->addAction(tr("del")), &QAction::triggered, this,
          &GyreFrame::del);

  statusText = new QLabel();
  scrollArea = new QScrollArea();
  scrollArea->setWidget(statusText);
  scrollArea->setWidgetResizable(true);
  scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

  QSizePolicy spStatus(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spStatus.setVerticalStretch(1);
  statusText->setSizePolicy(spStatus);

  auto layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(toolBar);
  layout->addWidget(scrollArea);

  setLayout(layout);

  QString out;

  auto error_text = devEnv->withException(
      [this, &out]() { out = devEnv->rep("(room :default)"); });

  statusText->setText(out + error_text);
}

}  // namespace gyreide
