#ifndef _LOCUS_SRC_LOCUS_CONSOLE_WIDGET_H_
#define _LOCUS_SRC_LOCUS_CONSOLE_WIDGET_H_

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

class QPaintEvent;
class QMouseEvent;

struct TextSelection;
struct TextPosition;

class ConsoleWidget : public QAbstractScrollArea {

  Q_OBJECT

 public:

  explicit ConsoleWidget(QWidget *parent = 0);

 protected:

  void paintEvent(QPaintEvent* event) override;

  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

 private:

  void drawCursor();

  TextPosition getTextPosition(const QPoint& pos) const;

  QStringList buffer_;
  QString line_;

  QSharedPointer<TextSelection> _selection;
};

#endif /* _LOCUS_SRC_LOCUS_CONSOLE_WIDGET_H_ */
