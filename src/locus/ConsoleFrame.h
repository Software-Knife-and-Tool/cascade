#ifndef _LOCUS_SRC_LOCUS_CONSOLE_WIDGET_H_
#define _LOCUS_SRC_LOCUS_CONSOLE_WIDGET_H_

#include <QAbstractScrollArea>
#include <QDebug>
#include <QFrame>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QScrollBar>
#include <QSharedPointer>
#include <QStringList>

class QPaintEvent;
class QMouseEvent;

struct TextSelection;
struct TextPosition;

class ConsoleFrame : public QAbstractScrollArea {

  Q_OBJECT

 public:

  explicit ConsoleFrame(QWidget *parent = 0);


 protected:

  void paintEvent(QPaintEvent* event);

  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);


 private:

  void drawCursor();

  TextPosition getTextPosition(const QPoint& pos) const;

  QStringList _buffer;
  QSharedPointer<TextSelection> _selection;
};

#endif /* _LOCUS_SRC_LOCUS_CONSOLE_WIDGET_H_ */
