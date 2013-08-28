#-------------------------------------------------
#
# Project created by QtCreator 2013-08-27T14:43:00
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Open_Graphics_Engine
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    model.cpp \
    camera.cpp \
    help_func.cpp \
    keyboardcontrol.cpp \
    mousecontrol.cpp \
    errorlog.cpp

HEADERS  += mainwindow.h \
    model.h \
    camera.h \
    help_func.h \
    keyboardcontrol.h \
    mousecontrol.h \
    errorlog.h
