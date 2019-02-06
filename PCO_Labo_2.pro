#-------------------------------------------------
#
# Project created by QtCreator 2015-02-12T16:05:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


TARGET = PCO_Labo_2
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    mythread.cpp \
    criticalsection.cpp

HEADERS  += dialog.h \
    mythread.h \
    criticalsection.h

FORMS    += dialog.ui
