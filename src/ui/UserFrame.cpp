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
 **  UserFrame.cpp: UserFrame implementation
 **
 **/
#include <QtWidgets>
#include <QString>

#include "UserFrame.h"

namespace logicaide {

void UserFrame::log(QString msg) {
  tabBar->log(msg);
}
  
void UserFrame::setContextStatus(QString str) {
  tabBar->setContextStatus(str);
}

void UserFrame::showEvent(QShowEvent* event) {
  QWidget::showEvent(event);
  tabBar->setContextStatus(name);
}

UserFrame::UserFrame(QString name, MainTabBar* tb) : tabBar(tb), name(name) {
    
  const char* html =
    "<html>"
    "  <body bgcolor=#c0c0c0>"
    "    <span style=\"text-align: center; font-family:Eaglefeather\">"
    "      <div>"
    "        <br>"
    "        <h1>Logica IDE <i>%1</i></h1>"
    "        <p></p>"
    "        <h2>running on <i>%2</i>, %3</h2>"
    "        <h2>%4</h2>"
    "        <p></p>"
    "      </div>"
    "      <p></p>"
    "    </span>"
    "  </body>"
    "</html>";

  auto user = tabBar->userInfo();
  
  auto system_html =
    QString(html).arg("0.0.5",
                      user->aboutHost(),
                      "an " + user->aboutCpu() + " system",
                      user->aboutSystem());

  bannerLabel = new QLabel(system_html);
  bannerLabel->setAlignment(Qt::AlignCenter);
  bannerLabel->setStyleSheet("color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);");

  layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(bannerLabel);
  
  setLayout(layout);
}

} /* logicaide namespace */
