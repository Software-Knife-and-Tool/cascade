/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  ScriptFrame.cpp: ScriptFrame implementation
 **
 **/
#include <QFileDialog>
#include <QLabel>
#include <QSplitter>
#include <QString>
#include <QTextEdit>
#include <QToolBar>
#include <QtWidgets>

#include "GyreEnv.h"
#include "ScriptFrame.h"

namespace gyreui {

#if 0
std::vector<struct tag> ScriptFrame::parse(QString src) {
  std::vector<struct tag> stack;

  return stack;
}
#endif

void ScriptFrame::clear() {
  editText->setText("");
  evalText->setText("");
}

void ScriptFrame::load() {
  loadFileName = QFileDialog::getOpenFileName(
      this, tr("Load File"), mw->userInfo()->userdir(), tr("File (*)"));

  QFile f(loadFileName);
  if (f.open(QFile::ReadOnly | QFile::Text)) {
    QTextStream in(&f);
    editText->setText(in.readAll());
    f.close();
  }

  saveFileName = loadFileName;
}

void ScriptFrame::evalFrame(GyreEnv*) {
  QString out;

  auto error = ideEnv->withException(
      [this, &out]() { out = ideEnv->rep(editText->toPlainText()); });

  evalText->setText(out + error);
}

QString ScriptFrame::evalString(QString expr, GyreEnv* env) {
  QString out;

  auto error =
      env->withException([env, expr, &out]() { out = env->rep(expr); });

  return out + error;
}

void ScriptFrame::reset() { ideEnv = new GyreEnv(); }

void ScriptFrame::del() {}

void ScriptFrame::save_as() {
  saveFileName =
      QFileDialog::getSaveFileName(this, tr("Save As"), "", tr("File (*)"));
  save();
}

void ScriptFrame::save() {
  QString text = editText->toPlainText();

  QSaveFile file(saveFileName);
  file.open(QIODevice::WriteOnly);
  file.write(text.toUtf8());
  file.commit();
}

bool ScriptFrame::eventFilter(QObject* watched, QEvent* event) {
  if (/* watched == textEdit && */ event->type() == QEvent::KeyPress) {
    QKeyEvent* e = static_cast<QKeyEvent*>(event);
    if (e->key() == Qt::Key_Return && e->modifiers() & Qt::ShiftModifier) {
      evalFrame(devEnv);
      return true;
    }
  }

  return mw->eventFilter(watched, event);
}

std::string ScriptFrame::script(std::string arg) {
  QRegExp rx("( |\".*\")");
  auto args = QString::fromStdString(arg);

  auto argv = args.remove('(').remove(')').split(rx);

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
#if 0
  auto home = getenv("HOME");
  auto path = QString::fromStdString(EnvironmentView::configFile);

  auto npath = home + path.remove(0, 1);
  log(";;; config file " + npath + " loaded");
  evalString("(load \"" + npath + "\")", ideEnv);
#endif
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

ScriptFrame::ScriptFrame(QString name, MainWindow* tb, GyreEnv* dev,
                         GyreEnv* ide)
    : mw(tb), devEnv(dev), ideEnv(ide), name(name) {
  auto size = this->frameSize();

  toolBar = new QToolBar();
  connect(toolBar->addAction(tr("clear")), &QAction::triggered, this,
          &ScriptFrame::clear);
  connect(toolBar->addAction(tr("load")), &QAction::triggered, this,
          &ScriptFrame::load);
  connect(toolBar->addAction(tr("eval")), &QAction::triggered, this,
          [this]() { evalFrame(devEnv); });
  connect(toolBar->addAction(tr("reset")), &QAction::triggered, this,
          &ScriptFrame::reset);
  connect(toolBar->addAction(tr("save")), &QAction::triggered, this,
          &ScriptFrame::save);
  connect(toolBar->addAction(tr("save as")), &QAction::triggered, this,
          &ScriptFrame::save_as);
  connect(toolBar->addAction(tr("del")), &QAction::triggered, this,
          &ScriptFrame::del);

  editText = new QTextEdit();
  editText->setMouseTracking(true);
  editScroll = new QScrollArea();
  editScroll->setWidget(editText);
  editScroll->setWidgetResizable(true);
  editScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  editScroll->installEventFilter(this);

  evalText = new QLabel();
  evalText->setMouseTracking(true);
  evalText->setAlignment(Qt::AlignTop);
  evalText->setMargin(3);
  evalText->setTextInteractionFlags(Qt::TextSelectableByMouse);
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

  evalString("(:defsym ide-context (cons " + scriptIdOf(script) + " " +
                 contextIdOf() + "))",
             ideEnv);

  loadConfigFile();
  setLayout(layout);
}

}  // namespace gyreui
