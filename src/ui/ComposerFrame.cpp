/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  ComposerFrame.cpp: ComposerFrame implementation
 **
 **/
#include <QFileDialog>
#include <QLabel>
#include <QSplitter>
#include <QString>
#include <QTextEdit>
#include <QToolBar>
#include <QtWidgets>

#include "ComposerFrame.h"
#include "GyreEnv.h"

namespace gyreide {

void ComposerFrame::clear() {
  editText->setText("");
  evalText->setText("");
}

void ComposerFrame::load() {
  loadFileName = QFileDialog::getOpenFileName(
      this, tr("Load File"), tabBar->userInfo()->userdir(), tr("File (*)"));

  QFile f(loadFileName);
  if (f.open(QFile::ReadOnly | QFile::Text)) {
    QTextStream in(&f);
    editText->setText(in.readAll());
    f.close();
  }

  saveFileName = loadFileName;
}

void ComposerFrame::eval() {
  QString out;

  tabBar->setContextStatus(tr("eval"));

  auto error = devEnv->withException(
      [this, &out]() { out = devEnv->rep(editText->toPlainText()); });

  evalText->setText(out + error);

  emit evalHappened(editText->toPlainText());
}

void ComposerFrame::macroexpand() {
  QString out;

  tabBar->setContextStatus(tr("macroexpand"));

  auto error = devEnv->withException([this, &out]() {
    auto mex = "(macroexpand (:quote " + editText->toPlainText() + "))";

    out = devEnv->rep(mex);
  });

  evalText->setText(out + error);
}

void ComposerFrame::describe() {
  QString out;

  tabBar->setContextStatus(tr("describe"));

  auto error = devEnv->withException([this, &out]() {
    auto mex = "(describe (:quote " + editText->toPlainText() + "))";

    out = devEnv->rep(mex);
  });

  evalText->setText(out + error);
}

void ComposerFrame::reset() { devEnv = new GyreEnv(); }

void ComposerFrame::del() {}

void ComposerFrame::save_as() {
  saveFileName =
      QFileDialog::getSaveFileName(this, tr("Save As"), "", tr("File (*)"));
  save();
}

void ComposerFrame::save() {
  QString text = editText->toPlainText();

  QSaveFile file(saveFileName);
  file.open(QIODevice::WriteOnly);
  file.write(text.toUtf8());
  file.commit();
}

bool ComposerFrame::eventFilter(QObject *watched, QEvent *event) {
  if (/* watched == textEdit && */ event->type() == QEvent::KeyPress) {
    QKeyEvent *e = static_cast<QKeyEvent *>(event);
    if (e->key() == Qt::Key_Return && e->modifiers() & Qt::ShiftModifier) {
      eval();
      return true;
    }
  }

  return tabBar->get_mw()->eventFilter(watched, event);
}

ComposerFrame::ComposerFrame(QString name, MainTabBar *tb, GyreEnv *cn)
    : tabBar(tb), devEnv(cn), name(name) {
  auto size = this->frameSize();

  toolBar = new QToolBar();
  connect(toolBar->addAction(tr("clear")), &QAction::triggered, this,
          &ComposerFrame::clear);
  connect(toolBar->addAction(tr("load")), &QAction::triggered, this,
          &ComposerFrame::load);
  connect(toolBar->addAction(tr("eval")), &QAction::triggered, this,
          &ComposerFrame::eval);
  connect(toolBar->addAction(tr("describe")), &QAction::triggered, this,
          &ComposerFrame::describe);
  connect(toolBar->addAction(tr("macroexpand")), &QAction::triggered, this,
          &ComposerFrame::macroexpand);
  connect(toolBar->addAction(tr("reset")), &QAction::triggered, this,
          &ComposerFrame::reset);
  connect(toolBar->addAction(tr("save")), &QAction::triggered, this,
          &ComposerFrame::save);
  connect(toolBar->addAction(tr("save as")), &QAction::triggered, this,
          &ComposerFrame::save_as);
  connect(toolBar->addAction(tr("del")), &QAction::triggered, this,
          &ComposerFrame::del);

  editText = new QTextEdit();
  editText->setMouseTracking(true);
  editScroll = new QScrollArea();
  editScroll->setWidget(editText);
  editScroll->setWidgetResizable(true);
  editScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  editScroll->installEventFilter(this);

  evalText = new QLabel();
  evalText->setMargin(3);
  evalText->setAlignment(Qt::AlignTop);
  evalText->setMouseTracking(true);
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
  editText->setMouseTracking(true);

  QSizePolicy spEval(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spEval.setVerticalStretch(1);
  evalText->setSizePolicy(spEval);
  evalText->setMouseTracking(true);

  auto vs = new QSplitter(Qt::Vertical, this);
  vs->addWidget(editScroll);
  vs->addWidget(evalScroll);

  auto layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(toolBar);
  layout->addWidget(vs);

  setLayout(layout);
}

}  // namespace gyreide
