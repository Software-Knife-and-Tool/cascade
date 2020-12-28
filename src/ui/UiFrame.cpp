/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  IdeFrame.cpp: IdeFrame implementation
 **
 **/
#include <QString>
#include <QtWidgets>

#include "ConsoleFrame.h"
#include "MainTabBar.h"
#include "ScriptFrame.h"
#include "UiFrame.h"

namespace gyreui {

void UiFrame::log(QString msg) { console->log(msg); }
const char* UiFrame::configFile = "~/.gyre-ide";
const char* UiFrame::version = "0.0.7";

void UiFrame::setContextStatus(QString str) { tabBar->setContextStatus(str); }

void UiFrame::showEvent(QShowEvent* event) {
  QWidget::showEvent(event);
  tabBar->setContextStatus(name);
}

GyreEnv* UiFrame::get_gyre() { return console->get_gyre(); }

UiFrame::UiFrame(QString name, MainTabBar* tb) : tabBar(tb), name(name) {
  std::string html =
      "<html>"
      "  <body bgcolor=#c0c0c0>"
      "    <span style=\"text-align: center; font-family:Eaglefeather\">"
      "      <div>"
      "        <br>"
      "        <h1>Gyre UI <i>%1</i></h1>"
      "        <p></p>"
      "        <h2>running on <i>%2</i>, %3</h2>"
      "        <h2>%4</h2>"
      "        <h2>configuration file: %5</h2>"
      "        <p></p>"
      "      </div>"
      "      <p></p>"
      "    </span>"
      "  </body>"
      "</html>";

  auto user = tabBar->userInfo();

  auto syshtml = QString::fromStdString(html).arg(
      version, user->aboutHost(), "an " + user->aboutCpu() + " system",
      user->aboutSystem(), configFile);

  bannerLabel = new QLabel(syshtml);
  bannerLabel->setAlignment(Qt::AlignCenter);

  auto top = new QFrame();

  auto tlayout = new QVBoxLayout;
  tlayout->setContentsMargins(5, 5, 5, 5);
  tlayout->addWidget(bannerLabel);

  top->setLayout(tlayout);
  top->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

  console = new ConsoleFrame("ide-console", tb);
  QSizePolicy policy = console->sizePolicy();
  policy.setVerticalStretch(1);
  console->setSizePolicy(policy);

  layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(top);
  layout->addWidget(console);

  setLayout(layout);
  setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
}

}  // namespace gyreui
