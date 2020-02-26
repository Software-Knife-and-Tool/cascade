#include "ConsoleWidget.h"

#include <QPainter>
#include <QScrollBar>
#include <QMouseEvent>
#include <QDebug>
  
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

  if(lhs.row == rhs.row) {
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
void ConsoleWidget::paintEvent(QPaintEvent* /*event*/) {

  QPainter painter(viewport());
  painter.fillRect(viewport()->rect(), Qt::white);

  QFontMetrics m = painter.fontMetrics();

  int current_line = verticalScrollBar()->value() / m.height();

  int y_offset = 0;

  int maximum_width = 0;

  while(y_offset < viewport()->height() && current_line >= 0 && current_line < _buffer.size()) {

    const int text_offset = y_offset + m.ascent();
    int x_offset = -horizontalScrollBar()->value();

    const QString& line = _buffer[current_line];

    foreach(const LineStyle& style, getLineStyle(*_selection.data(), line.size(), current_line)) {

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

  verticalScrollBar()->setRange(0, _buffer.size() * m.height());
  verticalScrollBar()->setSingleStep(m.height());
  verticalScrollBar()->setPageStep(viewport()->height());

  horizontalScrollBar()->setRange(0, qMax(maximum_width, horizontalScrollBar()->maximum()));
  horizontalScrollBar()->setSingleStep(m.averageCharWidth());
  horizontalScrollBar()->setPageStep(viewport()->width());
}

void ConsoleWidget::mousePressEvent(QMouseEvent* event) {
  QAbstractScrollArea::mousePressEvent(event);

  if(event->buttons().testFlag(Qt::LeftButton)) {
    _selection->start(getTextPosition(event->pos()));
  }

  update();
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

void ConsoleWidget::drawCursor() {

  //    const int x = m.width(_buffer[current_line], _selection->cursor().column);
  //    painter.setPen(QPen(Qt::red, 2));
  //    painter.drawLine(x, y_offset, x, y_offset +m.height());
  //    painter.setPen(Qt::black);
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
        m.width(_buffer[tp.row],
                current_column) < pos.x() + horizontalScrollBar()->value()) {

    if(++current_column >= _buffer[tp.row].size()) {
      break;
    }
  }

  tp.column = current_column;

  return tp;
}

ConsoleWidget::ConsoleWidget(QWidget *parent)
  : QAbstractScrollArea(parent), _selection(new TextSelection) {

  viewport()->setCursor(Qt::IBeamCursor);

  for(int i=0; i < 100; ++i) {
    _buffer << QString("1234567890ABCDEFGHIJKLMNOPQRTSUVWXYZ");
  }
}
