CONFIG += console c++14
  
DESTDIR = ../../build
ICON = ./tesseract.icns
INCLUDEPATH += . /usr/local/logica/canon
LIBS += /usr/local/logica/canon/libmu/mu.a
MOC_DIR = ../../build
OBJECTS_DIR = ../../build
TARGET = logicaide
TEMPLATE = app

HEADERS += \
           /usr/local/logica/canon/libmu/libmu.h \
           CanonEnv.h        \
           CanonFrame.h      \
           ComposerFrame.h   \
           ConsoleFrame.h    \
           IdeFrame.h        \
           InspectorFrame.h  \
           MainMenuBar.h     \
           MainTabBar.h      \
           MainWindow.h      \
           ScratchpadFrame.h \
           ScriptFrame.h     \
           ShellFrame.h      \
           StatusClock.h     \
           Tile.h            \
           ToolFrame.h       \
           TtyWidget.h       \
           UserFrame.h       \
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
           ScriptFrame.cpp   \
           ShellFrame.cpp    \
           Tile.cpp          \
           ToolFrame.cpp     \
           TtyWidget.cpp     \
           UserFrame.cpp     \
           main.cpp

QT += core gui widgets
