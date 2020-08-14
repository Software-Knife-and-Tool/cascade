CONFIG += console c++14
  
DESTDIR = ../../build
ICON = ./flash.icns
INCLUDEPATH += . /usr/local/logica
LIBS += /usr/local/logica/libmu/libmu.a
MOC_DIR = ../../build
OBJECTS_DIR = ../../build
TARGET = logicaide
TEMPLATE = app

HEADERS += \
           /usr/local/logica/libmu/libmu.h \
           CanonFrame.h      \
           ComposerFrame.h   \
           ConsoleFrame.h    \
           IdeFrame.h        \
           InspectorFrame.h  \
           MainMenuBar.h     \
           MainTabBar.h      \
           MainWindow.h      \
           ScratchpadFrame.h \
           StatusClock.h     \
           Tile.h            \
           ToolFrame.h       \
           TtyWidget.h       \
           UserFrame.h       \
           canon.h           \
           logica.h          \
           user.h

SOURCES += \
           CanonFrame.cpp    \
           ComposerFrame.cpp \
           ConsoleFrame.cpp  \
           IdeFrame.cpp      \
           InspectorFrame.cpp\
           MainMenuBar.cpp   \
           MainTabBar.cpp    \
           MainWindow.cpp    \
           ScratchpadFrame.cpp \
           Tile.cpp          \
           ToolFrame.cpp     \
           TtyWidget.cpp     \
           UserFrame.cpp     \
           main.cpp

QT += core gui widgets
