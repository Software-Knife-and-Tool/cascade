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
 **  ToolFrame.cpp: ToolFrame implementation
 **
 **/
#include <QtWidgets>
#include <QString>

#include "ToolFrame.h"

namespace composer {

ToolFrame::ToolFrame(QWidget*) : consoleWidget(new ConsoleWidget(this)) {
    
  auto hostName = QSysInfo::machineHostName();
  auto userName = qgetenv("USER");

  std::string html =
    "<html>"
    "  <body bgcolor=#c0c0c0>"
    "    <span style=\"text-align: center; font-family:Eaglefeather\">"
    "      <div>"
    "        <br>"
    "        <h1>Logica Composer IDE <i>0.0.2</i></h1>"
    "        <p></p>"f.
    "        <h2>running on <i>blackloch.local</i>, an Intel Core I7 workstation</h2>"
    "        <h2>macOs Mojave 10.14.6</h2>"
    "        <p></p>"
    "        <p>"
    "          <h3>"
    "            canon <i>0.0.1</i><br>"
    "            libmu <i>0.0.1</i><br>"
    "            mu <i>0.0.1</i>"
    "          </h3>"
    "        </p>"
    "        <p></p>"
    "      </div>"
    "      <p></p>"
    "    </span>"
    "  </body>"
    "</html>";
    
  auto system_html = QString::fromStdString(html);

  bannerLabel = new QLabel(system_html);
  bannerLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  bannerLabel->setAlignment(Qt::AlignCenter);
  bannerLabel->setStyleSheet("color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);");

  QSizePolicy console_policy = consoleWidget->sizePolicy();
  console_policy.setVerticalStretch(1);
  consoleWidget->setSizePolicy(console_policy);
  
  this->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  
  layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(bannerLabel);
  layout->addWidget(consoleWidget);
  
  this->setLayout(layout);
}

} /* composer namespace */
