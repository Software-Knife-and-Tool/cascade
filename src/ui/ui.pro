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
           FileMenu.h        \
           GyreEnv.h         \
           GyreFrame.h       \
           InspectorFrame.h  \
           MainMenuBar.h     \
           MainTabBar.h      \
           MainWindow.h      \
           PanelFrame.h      \
           ScratchpadFrame.h \
           ScriptFrame.h     \
           ShellFrame.h      \
           StatusClock.h     \
           Tile.h            \
           TtyWidget.h       \
           UiFrame.h         \
           UserFrame.h       \
           user.h

SOURCES += \
           ComposerFrame.cpp \
           ConsoleFrame.cpp  \
           GyreFrame.cpp     \
           InspectorFrame.cpp\
           MainMenuBar.cpp   \
           MainTabBar.cpp    \
           MainWindow.cpp    \
           PanelFrame.cpp    \
           ScratchpadFrame.cpp \
           ScriptFrame.cpp   \
           ShellFrame.cpp    \
           Tile.cpp          \
           TtyWidget.cpp     \
           UiFrame.cpp       \
           UserFrame.cpp     \
           main.cpp

QT += core gui widgets
