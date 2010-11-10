# -------------------------------------------------
# Project created by QtCreator 2010-10-25T11:09:38
# -------------------------------------------------
QT += core \
    gui \
    phonon

win32:RC_FILE = Resources/mainWindows.rc

TARGET = AkoosticPlayer
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    soundbutton.cpp \
    soundboard.cpp \
    boardselector.cpp \
    savepresetdialog.cpp \
    newsoundboarddialog.cpp
HEADERS += mainwindow.h \
    soundbutton.h \
    soundboard.h \
    boardselector.h \
    savepresetdialog.h \
    newsoundboarddialog.h
FORMS += mainwindow.ui \
    soundbutton.ui \
    soundboard.ui \
    boardselector.ui \
    savepresetdialog.ui \
    newsoundboarddialog.ui
OTHER_FILES += style.css
RESOURCES += Resources.qrc
