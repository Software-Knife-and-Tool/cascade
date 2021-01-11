CONFIG += console c++14
  
DESTDIR = ../../build
ICON = ./gyre.icns
INCLUDEPATH += . /opt/gyre/include
LIBS += /opt/gyre/lib/libmu.a
MOC_DIR = ../../build
OBJECTS_DIR = ../../build
TARGET = gyre-ui
TEMPLATE = app

HEADERS += \
           /opt/gyre/include/libmu/libmu.h \
           ComposerFrame.h   \
           ConsoleFrame.h    \
           EnvironmentView.h \
           FileMenu.h        \
           GyreEnv.h         \
           GyreFrame.h       \
           InspectorFrame.h  \
           MainMenuBar.h     \
           MainWindow.h      \
           PanelFrame.h      \
           ScratchpadFrame.h \
           ScriptFrame.h     \
           ShellFrame.h      \
           StatusClock.h     \
           Tile.h            \
           TtyWidget.h       \
           UserFrame.h       \
           user.h

SOURCES += \
           ComposerFrame.cpp   \
           ConsoleFrame.cpp    \
           EnvironmentView.cpp \
           GyreFrame.cpp       \
           InspectorFrame.cpp  \
           MainMenuBar.cpp     \
           MainWindow.cpp      \
           PanelFrame.cpp      \
           ScratchpadFrame.cpp \
           ScriptFrame.cpp     \
           ShellFrame.cpp      \
           Tile.cpp            \
           TtyWidget.cpp       \
           UserFrame.cpp       \
           main.cpp

QT += core gui widgets
