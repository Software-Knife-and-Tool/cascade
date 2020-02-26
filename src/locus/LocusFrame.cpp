#include <QtWidgets>

#include "LocusFrame.h"

namespace locus {

LocusFrame::LocusFrame() {

  const char* banner_html =
    "<div>"
    " <h1>Locus 0.0.1</h1>"
    " <br>"
    " <h3>Logica 0.1.0</h3>"
    "</div>";

  QString hostName = QSysInfo::machineHostName();
  QString userName = qgetenv("USER");

  QString system_html = QString("<div><h1>").arg(
                                        userName,
                                        QString(" on "),
                                        hostName,
                                        QString("</h1></div>"));
  
  topFiller = new QWidget;
  topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  bannerLabel = new QLabel(tr(banner_html));
  bannerLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  bannerLabel->setAlignment(Qt::AlignCenter);

  consoleWidget = new ConsoleWidget(this);
  
  bottomFiller = new QWidget;
  bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(topFiller);
  layout->addWidget(bannerLabel);
  layout->addWidget(consoleWidget);
  layout->addWidget(bottomFiller);
  this->setLayout(layout);

  this->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
}

} /* locus namespace */
