TEMPLATE = app
TARGET = locus
INCLUDEPATH += .
DESTDIR = ../../build
MOC_DIR = ../../build
OBJECTS_DIR = ../../build

HEADERS += locus.h        \
           ConsoleFrame.h \
           LocusFrame.h   \
           MainMenuBar.h  \
           MainWindow.h   \
           StatusClock.h

SOURCES += locus.cpp      \
           ConsoleFrame.cpp \           
           LocusFrame.cpp \           
           MainMenuBar.cpp\
           MainWindow.cpp \
           main.cpp

QT += core gui widgets
