CONFIG += console c++14
TEMPLATE = app
TARGET = locus
INCLUDEPATH += . /usr/local/logica
DESTDIR = ../../build
MOC_DIR = ../../build
OBJECTS_DIR = ../../build
LIBS += /usr/local/logica/libmu/libmu.a

HEADERS += \
           /usr/local/logica/libmu/libmu.h \
           ConsoleWidget.h \
           LocusFrame.h    \
           MainMenuBar.h   \
           MainWindow.h    \
           Mu.h            \
           StatusClock.h

SOURCES += \
           Mu.cpp            \
           ConsoleWidget.cpp \           
           LocusFrame.cpp    \           
           MainMenuBar.cpp   \
           MainWindow.cpp    \
           main.cpp

QT += core gui widgets
