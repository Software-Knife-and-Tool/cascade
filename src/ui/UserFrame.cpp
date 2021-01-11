/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  UserFrame.cpp: UserFrame implementation
 **
 **/
#include <QString>
#include <QtWidgets>

#include "EnvironmentView.h"
#include "UserFrame.h"

namespace gyreui {

void UserFrame::log(QString msg) { mw->log(msg); }

void UserFrame::setContextStatus(QString str) { mw->setContextStatus(str); }

void UserFrame::showEvent(QShowEvent* event) {
  QWidget::showEvent(event);
  mw->setContextStatus(name);
}

UserFrame::UserFrame(QString name, MainWindow* tb) : mw(tb), name(name) {
  const char* html =
      "<html>"
      "  <body bgcolor=#c0c0c0>"
      "    <span style=\"text-align: center; font-family:Eaglefeather\">"
      "      <div>"
      "        <br>"
      "        <h1>Gyre UI <i>%1</i></h1>"
      "        <p></p>"
      "        <h2>running on <i>%2</i>, %3</h2>"
      "        <h2>%4</h2>"
      "        <p></p>"
      "      </div>"
      "      <p></p>"
      "    </span>"
      "  </body>"
      "</html>";

  auto user = mw->userInfo();

  auto system_html = QString(html).arg(
      EnvironmentView::version, user->aboutHost(),
      "an " + user->aboutCpu() + " system", user->aboutSystem());

  bannerLabel = new QLabel(system_html);
  bannerLabel->setAlignment(Qt::AlignCenter);
  bannerLabel->setStyleSheet(
      "color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);");

  layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(bannerLabel);

  setLayout(layout);
}

}  // namespace gyreui
