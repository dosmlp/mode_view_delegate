#-------------------------------------------------
#
# Project created by QtCreator 2016-11-01T16:23:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = modelview
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    treemodel.cpp \
    itemdelegate.cpp

HEADERS  += widget.h \
    treemodel.h \
    itemdelegate.h
