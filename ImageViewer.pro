#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T05:45:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    opendatadialog.cpp \
    filepreviewdialog.cpp

HEADERS  += mainwindow.h \
    opendatadialog.h \
    filepreviewdialog.h

LIBS += -L/usr/local/lib -lexiv2

