#-------------------------------------------------
#
# Project created by QtCreator 2011-03-30T11:41:32
#
#-------------------------------------------------

QT       += core gui sql

CONFIG   += console

TARGET = jennicDaemon
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    databaseexplorer.cpp \
    nodeoverview.cpp \
    portselection.cpp

HEADERS  += mainwindow.h \
    databaseexplorer.h \
    logfile.h \
    nodeoverview.h \
    portselection.h

FORMS    += mainwindow.ui \
    databaseexplorer.ui \
    nodeoverview.ui \
    portselection.ui

RESOURCES += jennicDaemon.qrc

RC_FILE = appicon.qrc

LIBS    += -lanalogwidgets
LIBS    += -lqserialdeviced

unix:DEFINES   = _TTY_POSIX_
win32:DEFINES  = _TTY_WIN_
