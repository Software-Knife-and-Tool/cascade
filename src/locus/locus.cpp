#include <QDebug>
#include "locus.h"

namespace locus {
  
LocusPushButton::LocusPushButton(const QString &text) : QPushButton(text) {
  setObjectName("locus button");
  qDebug() << "locus Button has been constructed";
}

} /* namespace locus */
