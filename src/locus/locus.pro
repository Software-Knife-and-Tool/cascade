TEMPLATE = app
TARGET = locus
INCLUDEPATH += .

HEADERS += locus.h        \
           ConsoleWidget.h \
           LocusFrame.h   \
           MainMenuBar.h  \
           MainWindow.h   \
           StatusClock.h

SOURCES += locus.cpp      \
           ConsoleWidget.cpp \           
           LocusFrame.cpp \           
           MainMenuBar.cpp\
           MainWindow.cpp \
           main.cpp

QT += core gui widgets
