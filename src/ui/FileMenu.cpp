/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  FileMenu.cpp: FileMenu class
 **
 **/
#include <QtWidgets>

#include "FileMenu.h"
#include "MainMenuBar.h"
#include "MainWindow.h"

namespace gyreui {

void FileMenu::newFile() { mw->setContextStatus("<b>File|New</b>"); }
void FileMenu::openFile() { mw->setContextStatus("<b>File|Open</b>"); }
void FileMenu::saveFile() { mw->setContextStatus("<b>File|Save</b>"); }
void FileMenu::printFile() { mw->setContextStatus("<b>File|Print</b>"); }

FileMenu::FileMenu(MainMenuBar* mb) : mb(mb), mw(mb->mw_()) {}

} /* namespace gyreui */
