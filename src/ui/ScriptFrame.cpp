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
 **  ScriptFrame.cpp: ScriptFrame implementation
 **
 **/
#include <QFileDialog>
#include <QLabel>
#include <QSplitter>
#include <QTextEdit>
#include <QToolBar>
#include <QString>
#include <QtWidgets>

#include "CanonEnv.h"
#include "ScriptFrame.h"

namespace logicaide {
  
void ScriptFrame::clear() {
  editText->setText("");
  evalText->setText("");
}

void ScriptFrame::load() {
  loadFileName =
    QFileDialog::getOpenFileName(this,
                                 tr("Load File"),
                                 tabBar->userInfo()->userdir(),
                                 tr("File (*)"));

  QFile f(loadFileName);
  if (f.open(QFile::ReadOnly | QFile::Text)) {
    QTextStream in(&f);
    editText->setText(in.readAll());
    f.close();
  }

  saveFileName = loadFileName;
}
    
void ScriptFrame::evalFrame(CanonEnv* env) {
  QString out;

  auto error =
    ideEnv->withException([this, &out]() {
         out = ideEnv->rep(editText->toPlainText());
       });

  evalText->setText(out + error);
}

QString ScriptFrame::evalString(QString expr, CanonEnv* env) {
  QString out;

  auto error =
    env->withException([this, env, expr, &out]() {
         out = env->rep(expr);
       });
  
  return out + error;
}

void ScriptFrame::reset() {
  ideEnv = new CanonEnv();
}

void ScriptFrame::del() {
}

void ScriptFrame::save_as() {
  saveFileName = QFileDialog::getSaveFileName(this,
        tr("Save As"), "",
        tr("File (*)"));
  save();
}

void ScriptFrame::save() {
  QString text = editText->toPlainText();
  
  QSaveFile file(saveFileName);
  file.open(QIODevice::WriteOnly);
  file.write(text.toUtf8());
  file.commit();
}

bool ScriptFrame::eventFilter(QObject *watched, QEvent *event) {
  if ( /* watched == textEdit && */ event->type() == QEvent::KeyPress) {
    QKeyEvent *e = static_cast < QKeyEvent * >(event);
    if (e->key() == Qt::Key_Return &&
        e->modifiers() & Qt::ShiftModifier) {
      evalFrame(devEnv);
      return true;
    }
  }
    
  return tabBar->get_mw()->eventFilter(watched, event);
}

std::string ScriptFrame::script(std::string arg) {

  QRegExp rx("( |\".*\")");
  auto args = QString::fromStdString(arg);

  auto argv =
    args.remove('(')
        .remove(')')
        .split(rx);
  
  auto ctx = reinterpret_cast<ScriptFrame*>(argv.at(0).toULongLong());
  
  switch (hash(argv.at(1).toStdString().c_str())) {
    case hash("identity"):
      return argv[2].toStdString();
    case hash(":make"): {
      switch (hash(argv[2].toStdString().c_str())) {
        case hash("QMessageBox"): {
          QMessageBox msg;
          msg.setText(argv[3].toStdString().c_str());
          msg.exec();
          return argv[3].toStdString();
        }
        default:
          break;
      }
      break;
    }
    case hash(":show"):
      break;
    case hash(":hide"):
      break;
    case hash(":delete"):
      break;
    case hash(":log"):
      ctx->log(argv[2].toStdString().c_str());
      return argv[2].toStdString();
    default:
      break;
  }
  
  return "unimplemented-damnit";
}

void ScriptFrame::loadConfigFile() {
  auto home = getenv("HOME");
  auto path = QString::fromStdString(IdeFrame::configFile);

  auto npath = home + path.remove(0, 1);
  log(";;; config file " + npath + " loaded");
  evalString("(load \"" + npath + "\")", ideEnv);
}

#if 0
QString ScriptFrame::invoke(
                     std::string(* fn)(std::string),
                     QString arg) {
  
  auto fnp = reinterpret_cast<uint64_t>(fn);
  auto expr = QString("(invoke %1 \"%2\")").arg(fnp).arg(arg);
    
  QString buffer;
  auto error_text =
    ideEnv->withException([this, &buffer, expr]() {
      auto lines =
        this->ideEnv->rep(expr).split('\n', // version for princ/prin1?
                                      QString::SplitBehavior::KeepEmptyParts,
                                      Qt::CaseSensitive);
      buffer.append(lines.join("\n"));
    });
      
  if (error_text.size() > 1)
    buffer.append(error_text);

  return buffer.remove("\"");
}
#endif

ScriptFrame::ScriptFrame(QString name,
                         MainTabBar* tb,
                         CanonEnv* dev,
                         CanonEnv* ide)
  : tabBar(tb), devEnv(dev), ideEnv(ide), name(name) {
  
  auto size = this->frameSize();

  toolBar = new QToolBar();
  connect(toolBar->addAction(tr("clear")),
          &QAction::triggered, this, &ScriptFrame::clear);
  connect(toolBar->addAction(tr("load")),
          &QAction::triggered, this, &ScriptFrame::load);
  connect(toolBar->addAction(tr("eval")),
          &QAction::triggered, this, [this]() { evalFrame(devEnv); });
  connect(toolBar->addAction(tr("reset")),
          &QAction::triggered, this, &ScriptFrame::reset);
  connect(toolBar->addAction(tr("save")),
          &QAction::triggered, this, &ScriptFrame::save);
  connect(toolBar->addAction(tr("save as")),
          &QAction::triggered, this, &ScriptFrame::save_as);
  connect(toolBar->addAction(tr("del")),
          &QAction::triggered, this, &ScriptFrame::del);

  editText = new QTextEdit();
  editScroll = new QScrollArea();
  editScroll->setWidget(editText);
  editScroll->setWidgetResizable(true);
  editScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  editScroll->installEventFilter(this);

  evalText = new QLabel();
  evalScroll = new QScrollArea();
  evalScroll->setWidget(evalText);
  evalScroll->setWidgetResizable(true);
  evalScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  evalScroll->installEventFilter(this);
  evalScroll->setMinimumHeight(size.height() / 2);
  
  QSizePolicy spEdit(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spEdit.setVerticalStretch(1);
  editText->setSizePolicy(spEdit);

  QSizePolicy spEval(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spEval.setVerticalStretch(1);
  evalText->setSizePolicy(spEval);

  auto vs = new QSplitter(Qt::Vertical, this);
  vs->addWidget(editScroll);
  vs->addWidget(evalScroll);

  auto layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(toolBar);
  layout->addWidget(vs);

  evalString("(in-ns (ns \"logica-ide\" (ns-current)))", ideEnv);
  evalString("(:defcon ide-context (cons "
             + scriptIdOf(script)
             + " "
             + contextIdOf() + "))", ideEnv);

  loadConfigFile();
  setLayout(layout);
}

} /* logicaide namespace */
