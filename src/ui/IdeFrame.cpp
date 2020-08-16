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
 **  IdeFrame.cpp: IdeFrame implementation
 **
 **/
#include <QtWidgets>
#include <QString>

#include "ConsoleFrame.h"
#include "IdeFrame.h"
#include "MainTabBar.h"
#include "ScriptFrame.h"

namespace logicaide {

void IdeFrame::log(QString msg) { console->log(msg); }
  
void IdeFrame::setContextStatus(QString str) {
  tabBar->setContextStatus(str);
}

void IdeFrame::showEvent(QShowEvent* event) {
  QWidget::showEvent(event);
  tabBar->setContextStatus(name);
}

Canon* IdeFrame::get_canon() {
  return console->get_canon();
}
  
IdeFrame::IdeFrame(QString name, MainTabBar* tb)
  : tabBar(tb), name(name) {
  
  std::string html =
    "<html>"
    "  <body bgcolor=#c0c0c0>"
    "    <span style=\"text-align: center; font-family:Eaglefeather\">"
    "      <div>"
    "        <br>"
    "        <h1>Logica IDE <i>%1</i></h1>"
    "        <p></p>"
    "        <h2>running on <i>%2</i>, %3</h2>"
    "        <h2>%4</h2>"
    "        <h2>configuration file: " + ScriptFrame::configFile + "</h2>"
    "        <p></p>"
    "      </div>"
    "      <p></p>"
    "    </span>"
    "  </body>"
    "</html>";

  auto user = tabBar->userInfo();
  
  auto syshtml =
    QString::fromStdString(html).arg("0.0.6",
                                     user->aboutHost(),
                                     "an " + user->aboutCpu() + " system",
                                     user->aboutSystem());

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

} /* logicaide namespace */
