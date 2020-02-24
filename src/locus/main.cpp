#include <QApplication>
#include "locus.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
    
  locus::LocusPushButton button("quit");
  button.resize(100, 30);

  button.show();
  return app.exec();
}

