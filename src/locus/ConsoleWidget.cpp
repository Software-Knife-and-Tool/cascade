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
 **  ConsoleWidget.cpp: ConsoleWidget implementation
 **
 **/

#include "ConsoleWidget.h"

#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>

namespace locus {
  
struct LineStyle {

  LineStyle(const QColor& bg, const QColor& fg, int s, int l) : background(bg), foreground(fg), start(s), length(l) {}

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
  }
  else {
    return lhs.row < rhs.row;
  }
}

bool operator==(const TextPosition& lhs, const TextPosition& rhs) {
  return lhs.row == rhs.row && lhs.column == rhs.column;
}


bool operator!=(const TextPosition& lhs, const TextPosition& rhs) {
  return ! (lhs == rhs);
}

struct TextSelection {

  const TextPosition& first() const {
    return (start_pos < end_pos) ? start_pos : end_pos;
  }

  const TextPosition& last() const {
    return (first() == start_pos) ? end_pos : start_pos;
  }

  const TextPosition& cursor() const {
    return last();
  }

  void start(const TextPosition& pos) {
    start_pos = pos;
    end_pos = pos;
  }

  void end(const TextPosition& pos) {
    end_pos = pos;
  }

  int lines() const {
    return last().row - first().row + 1;
  }

  bool hasActiveSelection() const {
    return start_pos != end_pos;
  }

  TextPosition start_pos;
  TextPosition end_pos;
};

inline LineStyle normalStyle(int start, int length) {
  return LineStyle(Qt::white, Qt::black, start, length);
}

inline LineStyle highlightStyle(int start, int length) {
  return LineStyle(Qt::darkGray, Qt::white, start, length);
}

QList<LineStyle> getLineStyle(const TextSelection& sel, int length, int row) {

  QList<LineStyle> styles;

  if(! sel.hasActiveSelection()) {
    styles << normalStyle(0, length);
  } else if(sel.first().row == row && sel.last().row == row) {

    styles << normalStyle(0, sel.first().column);
    styles << highlightStyle(sel.first().column, sel.last().column - sel.first().column);

    styles << normalStyle(sel.last().column, length - sel.last().column + 1);
  } else if(sel.first().row == row) {

    styles << normalStyle(0, sel.first().column);
    styles << highlightStyle(sel.first().column, length - sel.first().column + 1);
  } else if(sel.last().row == row) {

    styles << highlightStyle(0, sel.last().column);
    styles << normalStyle(sel.last().column, length - sel.last().column + 1);
  } else if(sel.first().row < row && sel.last().row > row) {
    styles << highlightStyle(0, length);
  } else {
    styles << normalStyle(0, length);
  }

  return styles;
}

int drawWidth(QPainter& painter, const QString& text) {
  //return painter.boundingRect(QRect(), Qt::AlignLeft, text).width();
  return painter.fontMetrics().width(text);
}

/** * class members **/
void ConsoleWidget::paintEvent(QPaintEvent*) {

  QPainter painter(viewport());
  painter.fillRect(viewport()->rect(), Qt::white);

  QFontMetrics m = painter.fontMetrics();

  int current_line = verticalScrollBar()->value() / m.height();

  int y_offset = 0;
  int maximum_width = 0;

  /* display the buffer */
  while (y_offset < viewport()->height() && current_line >= 0 && current_line < buffer_.size()) {

    const int text_offset = y_offset + m.ascent();
    int x_offset = -horizontalScrollBar()->value();

    const QString& line = buffer_[current_line];

    foreach (const auto style, getLineStyle(*_selection.data(), line.size(), current_line)) {

      painter.setPen(style.foreground);
      painter.setBrush(style.background);

      const QString text = line.mid(style.start, style.length);
      int text_width = drawWidth(painter, text);

      painter.fillRect(QRect(x_offset, y_offset, text_width, m.height()), style.background);

      painter.drawText(x_offset, text_offset, text);
      x_offset += text_width;
    }

    maximum_width = qMax(maximum_width, m.width(line));

    y_offset += m.height();

    ++current_line;
  }

  /* display the prompt */
  int x_offset = -horizontalScrollBar()->value();
      
  if (y_offset < viewport()->height() && current_line >= 0 && prompt_.size() > 0) {

    const int text_offset = y_offset + m.ascent();

    foreach (const auto style, getLineStyle(*_selection.data(), prompt_.size(), current_line)) {
    
      painter.setPen(style.foreground);
      painter.setBrush(style.background);

      const QString text = prompt_.mid(style.start, style.length);
      int text_width = drawWidth(painter, text);
      
      painter.fillRect(QRect(x_offset, y_offset, text_width, m.height()), style.background);
      painter.drawText(x_offset, text_offset, text);

      x_offset += text_width;
    }
  }

  /* display the current line */
  if (y_offset < viewport()->height() && current_line >= 0 && line_.size() > 0) {

    const int text_offset = y_offset + m.ascent();

    foreach (const auto style, getLineStyle(*_selection.data(), line_.size(), current_line)) {
    
      painter.setPen(style.foreground);
      painter.setBrush(style.background);

      const QString text = line_.mid(style.start, style.length);
      int text_width = drawWidth(painter, text);
      
      painter.fillRect(QRect(x_offset, y_offset, text_width, m.height()), style.background);
      painter.drawText(x_offset, text_offset, text);

      x_offset += text_width;
    }
  }

  /* display the cursor */
  if (y_offset < viewport()->height() && current_line >= 0 && cursor_.size() > 0) {

    const int text_offset = y_offset + m.ascent();

    foreach (const auto style, getLineStyle(*_selection.data(), cursor_.size(), current_line)) {
    
      painter.setPen(style.foreground);
      painter.setBrush(style.background);

      const QString text = cursor_.mid(style.start, style.length);
      int text_width = drawWidth(painter, text);
      
      painter.fillRect(QRect(x_offset, y_offset, text_width, m.height()), style.background);
      painter.drawText(x_offset, text_offset, text);
    }
  }
  
  verticalScrollBar()->setRange(0, buffer_.size() * m.height());
  verticalScrollBar()->setSingleStep(m.height());
  verticalScrollBar()->setPageStep(viewport()->height());

  horizontalScrollBar()->setRange(0, qMax(maximum_width, horizontalScrollBar()->maximum()));
  horizontalScrollBar()->setSingleStep(m.averageCharWidth());
  horizontalScrollBar()->setPageStep(viewport()->width());
}

void ConsoleWidget::drawCursor() {

  // const int x = m.width(buffer_[current_line], _selection->cursor().column);
  // painter.setPen(QPen(Qt::red, 2));
  // painter.drawLine(x, y_offset, x, y_offset + m.height());
  // painter.setPen(Qt::black);
}

TextPosition ConsoleWidget::getTextPosition(const QPoint& pos) const {

  QFontMetrics m(font());

  int current_line = 0;

  while(current_line * m.height() < pos.y()) {
    ++current_line;
  }

  TextPosition tp;
  tp.row = current_line + verticalScrollBar()->value() / m.height() - 1;

  int current_column = 0;

  while(tp.row >= 0 &&
        m.width(buffer_[tp.row],
                current_column) < pos.x() + horizontalScrollBar()->value()) {

    if(++current_column >= buffer_[tp.row].size()) {
      break;
    }
  }

  tp.column = current_column;

  return tp;
}

/** * events **/
void ConsoleWidget::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Return:
      buffer_ << prompt_ + line_;
      mu->withException([this]() {
                          buffer_ << mu->mu(line_);
                        });
      line_.clear();
      viewport()->update();
      break;
    case Qt::Key_Backspace:
      line_.resize(line_.size() - 1);
      viewport()->update();
      break;
    default:
      line_.append(event->text());
      viewport()->update();
      break;
  }
}

void ConsoleWidget::keyReleaseEvent(QKeyEvent *) { }

void ConsoleWidget::mousePressEvent(QMouseEvent*) {
#if 0
  QAbstractScrollArea::mousePressEvent(event);


  if (event->buttons().testFlag(Qt::LeftButton)) {
    _selection->start(getTextPosition(event->pos()));
  }
  
  this->viewport()->update();
#endif
}

void ConsoleWidget::mouseReleaseEvent(QMouseEvent* event) {

  QAbstractScrollArea::mouseReleaseEvent(event);
}

void ConsoleWidget::mouseMoveEvent(QMouseEvent* event) {
  
  QAbstractScrollArea::mouseMoveEvent(event);

  if(event->buttons().testFlag(Qt::LeftButton)) {
    _selection->end(getTextPosition(event->pos()));
  }

  update();
}

/** * constructor **/
ConsoleWidget::ConsoleWidget(QWidget *parent, locus::Mu* mu)
  : QAbstractScrollArea(parent),
    mu(mu),
    _selection(new TextSelection) {

  viewport()->setCursor(Qt::IBeamCursor);
  buffer_ << QString(";;; mu ").append(mu->version());
  prompt_ = QString("> ");
  cursor_ = QString("_");
}
} /* locus namespace */
