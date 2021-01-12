/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  FileView.cpp: FileView class
 **
 **/
#include <QtWidgets>

#include "FileView.h"
#include "MainMenuBar.h"
#include "MainWindow.h"

namespace gyreui {

void FileView::newFile() { mw->setContextStatus("<b>File|New</b>"); }
void FileView::openFile() { mw->setContextStatus("<b>File|Open</b>"); }
void FileView::saveFile() { mw->setContextStatus("<b>File|Save</b>"); }
void FileView::printFile() { mw->setContextStatus("<b>File|Print</b>"); }

FileView::FileView(MainMenuBar* mb) : mb(mb), mw(mb->mw_()) {}

} /* namespace gyreui */
