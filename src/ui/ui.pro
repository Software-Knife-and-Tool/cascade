CONFIG += console c++14
  
DESTDIR = ../../build
ICON = ./flash.icns
INCLUDEPATH += . /usr/local/logica
LIBS += /usr/local/logica/libmu/libmu.a
MOC_DIR = ../../build
OBJECTS_DIR = ../../build
TARGET = composer
TEMPLATE = app

HEADERS += \
           /usr/local/logica/libmu/libmu.h \
           ComposerFrame.h   \
           ConsoleWidget.h   \
           MainMenuBar.h     \
           MainTabBar.h      \
           MainWindow.h      \
           StatusClock.h     \
           ToolFrame.h       \
           canon.h           \
           logica.h

SOURCES += \
           ComposerFrame.cpp \           
           ConsoleWidget.cpp \           
           MainMenuBar.cpp   \
           MainTabBar.cpp    \
           MainWindow.cpp    \
           ToolFrame.cpp     \           
           main.cpp

QT += core gui widgets
