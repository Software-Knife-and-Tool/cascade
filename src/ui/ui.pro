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
           ComposerFrame.h \
           ConsoleWidget.h \
           MainMenuBar.h   \
           MainWindow.h    \
           Mu.h            \
           StatusClock.h   \
           UiFrame.h

SOURCES += \
           ComposerFrame.cpp \           
           ConsoleWidget.cpp \           
           MainMenuBar.cpp   \
           MainWindow.cpp    \
           UiFrame.cpp       \           
           main.cpp

QT += core gui widgets
