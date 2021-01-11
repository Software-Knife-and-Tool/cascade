/********
 **
 **  SPDX-License-Identifier: BSD-3-Clause
 **
 **  Copyright (c) 2017-2021 James M. Putnam <putnamjm.design@gmail.com>
 **
 **/

/********
 **
 **  StatusClock.h: StatusClock class
 **
 **/
#ifndef GYREUI_UI_STATUSCLOCK_H_
#define GYREUI_UI_STATUSCLOCK_H_

#include <QDateTime>
#include <QLabel>
#include <QMainWindow>
#include <QStatusBar>
#include <QTimer>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QStatusBar;
class QDateTime;
QT_END_NAMESPACE

namespace gyreui {

class MainWindow;

class StatusClock : public QObject {
  Q_OBJECT

 public:
  StatusClock(QStatusBar*, QLabel* dl)
      : timer(new QTimer(this)), dateLabel(dl) {
    connect(timer, SIGNAL(timeout()), this, SLOT(statusClock()));
    timer->start(1000);
  }

 public slots:
  void statusClock() {
    QDateTime now = QDateTime::currentDateTime();
    dateLabel->setText(now.toString("ddd MMMM d yy h:mm ap "));
  }

 private:
  QTimer* timer;
  QLabel* dateLabel;
};

}  // namespace gyreui

#endif /* GYREUI_UI_STATUSCLOCK_H_ */
