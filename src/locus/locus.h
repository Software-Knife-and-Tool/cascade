#ifndef _LOGICA_SRC_LOCUS_H_
#define _LOGICA_SRC_LOCUS_H_

#include <QPushButton>

namespace locus {
  
class LocusPushButton : public QPushButton {
 public:
  LocusPushButton(const QString &text);
};

} /* locus namespace */

#endif /* _LOGICA_SRC_LOCUS_H_ */ 
