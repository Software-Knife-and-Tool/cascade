#include <QDesktopWidget>
#include <QApplication>

#include "MainWindow.h"

int main(int argc, char **argv) {

  QApplication app(argc, argv);
  
  locus::MainWindow mainWindow;
  mainWindow.show();
  
  mainWindow.setFixedSize(1024, 768);
  return app.exec();
}
