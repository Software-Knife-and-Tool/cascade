#ifndef _LOCUS_SRC_LOCUS_HOMEFRAME_H_
#define _LOCUS_SRC_LOCUS_HOMEFRAME_H_

#include <QWidget>
#include <QFrame>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QWidget;
class QLabel;
QT_END_NAMESPACE

namespace locus {
  
class HomeFrame : public QFrame {
  Q_OBJECT

 public:
  HomeFrame();

 protected:

 private:
  QVBoxLayout *layout;
  QWidget *topFiller;
  QWidget *bottomFiller;
  QLabel *bannerLabel;
};

} /* locus namespace */

#endif  /* _LOCUS_SRC_LOCUS_HOMEFRAME_H_ */
