/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  TtyWidget.cpp: TtyWidget implementation
 **
 **/
#include "TtyWidget.h"

#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>

namespace gyreide {

struct LineStyle {
  LineStyle(const QColor& bg, const QColor& fg, int s, int l)
      : background(bg), foreground(fg), start(s), length(l) {}

  QBrush background;
  QPen foreground;

  int start;
  int length;
};

struct TextPosition {
  TextPosition(int r = 0, int c = 0) : row(r), column(c) {}

  int row;
  int column;
};

bool operator<(const TextPosition& lhs, const TextPosition& rhs) {
  if (lhs.row == rhs.row) {
    return lhs.column < rhs.column;
  } else {
    return lhs.row < rhs.row;
  }
}

bool operator==(const TextPosition& lhs, const TextPosition& rhs) {
  return lhs.row == rhs.row && lhs.column == rhs.column;
}

bool operator!=(const TextPosition& lhs, const TextPosition& rhs) {
  return !(lhs == rhs);
}

struct TextSelection {
  const TextPosition& first() const {
    return (start_pos < end_pos) ? start_pos : end_pos;
  }

  const TextPosition& last() const {
    return (first() == start_pos) ? end_pos : start_pos;
  }

  const TextPosition& cursor() const { return last(); }

  void start(const TextPosition& pos) {
    start_pos = pos;
    end_pos = pos;
  }

  void end(const TextPosition& pos) { end_pos = pos; }

  int lines() const { return last().row - first().row + 1; }

  bool hasActiveSelection() const { return start_pos != end_pos; }

  TextPosition start_pos;
  TextPosition end_pos;
};

inline LineStyle normalStyle(int start, int length) {
  return LineStyle(Qt::white, Qt::black, start, length);
}

inline LineStyle highlightStyle(int start, int length) {
  return LineStyle(Qt::darkGray, Qt::white, start, length);
}

namespace {

QList<LineStyle> getLineStyle(const TextSelection& sel, int length, int row) {
  QList<LineStyle> styles;

  if (!sel.hasActiveSelection()) {
    styles << normalStyle(0, length);
  } else if (sel.first().row == row && sel.last().row == row) {
    styles << normalStyle(0, sel.first().column);
    styles << highlightStyle(sel.first().column,
                             sel.last().column - sel.first().column);

    styles << normalStyle(sel.last().column, length - sel.last().column + 1);
  } else if (sel.first().row == row) {
    styles << normalStyle(0, sel.first().column);
    styles << highlightStyle(sel.first().column,
                             length - sel.first().column + 1);
  } else if (sel.last().row == row) {
    styles << highlightStyle(0, sel.last().column);
    styles << normalStyle(sel.last().column, length - sel.last().column + 1);
  } else if (sel.first().row < row && sel.last().row > row) {
    styles << highlightStyle(0, length);
  } else {
    styles << normalStyle(0, length);
  }

  return styles;
}

int drawWidth(QPainter& painter, const QString& text) {
  // return painter.boundingRect(QRect(), Qt::AlignLeft, text).width();
  return painter.fontMetrics().horizontalAdvance(text);
}

} /* anonymous namespace */

/** * draw text line **/
void TtyWidget::DrawLine(int& x_offset, int y_offset, QString line,
                         QFontMetrics m, int current_line) {
  static const int XOFF = 5;
  static const int YOFF = 5;

  QPainter painter(viewport());

  if (y_offset < viewport()->height() && current_line >= 0 && line.size() > 0) {
    const int text_offset = y_offset + m.ascent();

    foreach (const auto style,
             getLineStyle(*_selection.data(), line.size(), current_line)) {
      painter.setPen(style.foreground);
      painter.setBrush(style.background);

      const QString text = line.mid(style.start, style.length);
      int text_width = drawWidth(painter, text);

      painter.fillRect(
          QRect(x_offset + XOFF, y_offset + YOFF, text_width, m.height()),
          style.background);
      painter.drawText(x_offset + XOFF, text_offset + YOFF, text);
      x_offset += text_width;
    }
  }
}

/** * class members **/
void TtyWidget::paintEvent(QPaintEvent*) {
  QPainter painter(viewport());
  painter.fillRect(viewport()->rect(), Qt::white);

  QFontMetrics m = painter.fontMetrics();

  int current_line = verticalScrollBar()->value() / m.height();

  int y_offset = 0;
  int x_offset = 0;
  int maximum_width = 0;

  /* display the buffer */
  while (y_offset < viewport()->height() && current_line >= 0 &&
         current_line < buffer_.size()) {
    x_offset = -horizontalScrollBar()->value();

    DrawLine(x_offset, y_offset, buffer_[current_line], m, current_line);

    maximum_width =
        qMax(maximum_width, m.horizontalAdvance(buffer_[current_line]));

    y_offset += m.height();
    ++current_line;
  }

  /* display the prompt */
  x_offset = -horizontalScrollBar()->value();
  DrawLine(x_offset, y_offset, prompt_, m, current_line);
  /* display the current line */
  DrawLine(x_offset, y_offset, line_, m, current_line);
  /* display the cursor */
  DrawLine(x_offset, y_offset, cursor_, m, current_line);

  maximum_width = qMax(maximum_width, m.horizontalAdvance(prompt_) +
                                          m.horizontalAdvance(line_) +
                                          m.horizontalAdvance(cursor_));

  verticalScrollBar()->setRange(0, buffer_.size() * m.height());
  verticalScrollBar()->setSingleStep(m.height());
  verticalScrollBar()->setPageStep(viewport()->height());

  horizontalScrollBar()->setRange(
      0, qMax(maximum_width, horizontalScrollBar()->maximum()));
  horizontalScrollBar()->setSingleStep(m.averageCharWidth());
  horizontalScrollBar()->setPageStep(viewport()->width());
}

void TtyWidget::DrawCursor() {
  // const int x = m.width(buffer_[current_line], _selection->cursor().column);
  // painter.setPen(QPen(Qt::red, 2));
  // painter.drawLine(x, y_offset, x, y_offset + m.height());
  // painter.setPen(Qt::black);
}

TextPosition TtyWidget::getTextPosition(const QPoint& pos) const {
  QFontMetrics m(font());

  int current_line = 0;

  while (current_line * m.height() < pos.y()) {
    ++current_line;
  }

  TextPosition tp;
  tp.row = current_line + verticalScrollBar()->value() / m.height() - 1;

  int current_column = 0;

  if (tp.row < buffer_.size() - 1) {
    while (tp.row >= 0 && m.horizontalAdvance(buffer_[tp.row], current_column) <
                              pos.x() + horizontalScrollBar()->value()) {
      if (++current_column >= buffer_[tp.row].size()) {
        break;
      }
    }
  }

  tp.column = current_column;

  return tp;
}

/** * events **/
void TtyWidget::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key_Return: {
      buffer_ << prompt_ + line_;

      auto error_text = ideEnv->withException([this]() {
        auto lines = ideEnv->rep(line_).split(
            '\n', QString::SplitBehavior::KeepEmptyParts, Qt::CaseSensitive);
        for (int i = 0; i < lines.size(); ++i) buffer_ << lines.at(i);
      });

      if (error_text.size() > 1) buffer_ << error_text;

      line_.clear();
      break;
    }
    case Qt::Key_Backspace:
      line_.resize(line_.size() - 1);
      break;
    default:
      line_.append(event->text());
      break;
  }

  viewport()->update();
}

void TtyWidget::keyReleaseEvent(QKeyEvent*) {}

void TtyWidget::mousePressEvent(QMouseEvent*) {
#if 0
  QAbstractScrollArea::mousePressEvent(event);

  if (event->buttons().testFlag(Qt::LeftButton)) {
    TextPosition tp = getTextPosition(event->pos());
    if (tp.row < buffer_.size())
      _selection->start(tp);
  }
  
  this->viewport()->update();
#endif
}

void TtyWidget::mouseReleaseEvent(QMouseEvent* event) {
  QAbstractScrollArea::mouseReleaseEvent(event);
}

void TtyWidget::mouseMoveEvent(QMouseEvent* event) {
#if 0
  QAbstractScrollArea::mouseMoveEvent(event);

  if(event->buttons().testFlag(Qt::LeftButton)) {
    TextPosition tp = getTextPosition(event->pos());
    if (tp.row < buffer_.size())
      _selection->end(tp);
  }

  update();
#endif
}

void TtyWidget::writeTty(QString str) {
  buffer_ << str;
  ;
}

/** * constructor **/
TtyWidget::TtyWidget(QWidget* parent)
    : QAbstractScrollArea(parent),
      ideEnv(new GyreEnv()),
      _selection(new TextSelection) {
  viewport()->setCursor(Qt::IBeamCursor);
  buffer_ << QString(";;; gyre ").append(ideEnv->version());
  prompt_ = QString(". ");
  cursor_ = QString("_");
}

}  // namespace gyreide
