#ifndef _LOCUS_SRC_LOCUS_LOCUSFRAME_H_
#define _LOCUS_SRC_LOCUS_LOCUSFRAME_H_

#include <QWidget>
#include <QFrame>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QWidget;
class QLabel;
QT_END_NAMESPACE

namespace locus {
  
class LocusFrame : public QFrame {
  Q_OBJECT

 public:
  LocusFrame();

 protected:

 private:
  QVBoxLayout *layout;
  QWidget *topFiller;
  QWidget *bottomFiller;
  QLabel *bannerLabel;
};

} /* locus namespace */

#endif  /* _LOCUS_SRC_LOCUS_LOCUSFRAME_H_ */
