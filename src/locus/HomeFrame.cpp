#include <QtWidgets>

#include "HomeFrame.h"

namespace locus {

HomeFrame::HomeFrame() {

  const char* banner_html =
    "<div>"
    " <h1>Locus 0.0.0</h1>"
    " <br>"
    " <h3>Logica 0.1.0</h3>"
    "</div>";

  topFiller = new QWidget;
  topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  bannerLabel = new QLabel(tr(banner_html));
  bannerLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  bannerLabel->setAlignment(Qt::AlignCenter);

  bottomFiller = new QWidget;
  bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(topFiller);
  layout->addWidget(bannerLabel);
  layout->addWidget(bottomFiller);
  this->setLayout(layout);

  setMinimumSize(160, 160);
  resize(480, 320);
}

} /* locus namespace */
