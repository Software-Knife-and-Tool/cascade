CONFIG += console c++14
  
DESTDIR = ../../build
INCLUDEPATH += . /usr/local/logica
LIBS += /usr/local/logica/libmu/libmu.a
MOC_DIR = ../../build
OBJECTS_DIR = ../../build
TARGET = cascade
TEMPLATE = app

HEADERS += \
           /usr/local/logica/libmu/libmu.h \
           CascadeFrame.h  \
           ComposerFrame.h \
           ConsoleWidget.h \
           MainMenuBar.h   \
           MainWindow.h    \
           Mu.h            \
           StatusClock.h

SOURCES += \
           CascadeFrame.cpp       \           
           ComposerFrame.cpp \           
           ConsoleWidget.cpp \           
           MainMenuBar.cpp   \
           MainWindow.cpp    \
           main.cpp

QT += core gui widgets
