/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  TtyWidget.h: TtyWidget class
 **
 **/
#ifndef _GYREIDE_SRC_UI_TTYWIDGET_H_
#define _GYREIDE_SRC_UI_TTYWIDGET_H_

#include <QAbstractScrollArea>
#include <QDebug>
#include <QFrame>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QScrollBar>
#include <QSharedPointer>
#include <QStringList>

#include "GyreEnv.h"

class QPaintEvent;
class QMouseEvent;

namespace gyreide {

struct TextSelection;
struct TextPosition;

class TtyWidget : public QAbstractScrollArea {
  Q_OBJECT

 public:
  explicit TtyWidget(QWidget*);

  void writeTty(QString);

  GyreEnv* get_gyre() { return ideEnv; }

 protected:
  void paintEvent(QPaintEvent* event) override;

  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;

 private:
  void DrawCursor();
  void DrawLine(int&, int, QString, QFontMetrics, int);

  TextPosition getTextPosition(const QPoint& pos) const;

  QString cursor_;
  QString line_;
  QString prompt_;
  QStringList buffer_;

  GyreEnv* ideEnv;
  QSharedPointer<TextSelection> _selection;
};

}  // namespace gyreide

#endif /* _GYREIDE_SRC_UI_CONSOLEWIDGET_H_ */
