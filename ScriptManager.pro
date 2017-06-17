#-------------------------------------------------
#
# Project created by QtCreator 2017-06-04T18:38:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScriptManager
TEMPLATE = app


SOURCES += main.cpp \
    scriptrunner.cpp \
    logwindow.cpp \
    filebrowser.cpp \
    mainwindow.cpp \
    dynamicparameter.cpp

HEADERS  += \
    defines.h \
    scriptrunner.h \
    logwindow.h \
    filebrowser.h \
    mainwindow.h \
    dynamicparameter.h

RESOURCES += \
    resources.qrc
