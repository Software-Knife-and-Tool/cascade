#ifndef _LOCUS_SRC_LOCUS_STATUSCLOCK_H_
#define _LOCUS_SRC_LOCUS_STATUSCLOCK_H_

#include <QMainWindow>
#include <QWidget>
#include <QStatusBar>
#include <QTimer>
#include <QDateTime>
#include <QLabel>

QT_BEGIN_NAMESPACE
class QLabel;
class QStatusBar;
class QDateTime;
QT_END_NAMESPACE

namespace locus {

class MainWindow;
  
class StatusClock : public QObject {
  Q_OBJECT
    
 public:
  QStatusBar *statusBar;
  QTimer *timer;
  QLabel *dateLabel;
    
  StatusClock(QStatusBar *sb, QLabel *dl)
    : statusBar(sb), timer(new QTimer(this)), dateLabel(dl) {
    
    connect(timer, SIGNAL(timeout()), this, SLOT(statusClock()));
    timer->start(1000);
  }

 public slots:
  void statusClock() {
    
    QDateTime now = QDateTime::currentDateTime();
    dateLabel->setText(now.toString("ddd MMMM d yy h:m ap"));
  }
};

} /* locus namespace */

#endif  /* _LOCUS_SRC_LOCUS_STATUSCLOCK_H_ */
