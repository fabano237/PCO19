QT       += core websockets
QT       -= gui

TARGET = fileserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    fileserver.cpp \
    filereader.cpp \
    requesthandler.cpp \
    requestthread.cpp \
    requestdispatcherthread.cpp \
    responsedispatcherthread.cpp \
    runnabletask.cpp \
    threadpool.cpp \
    workerthread.cpp

HEADERS += \
    fileserver.h \
    filereader.h \
    response.h \
    abstractbuffer.h \
    mesabuffer.h \
    request.h \
    requesthandler.h \
    requestthread.h \
    requestdispatcherthread.h \
    responsedispatcherthread.h \
    runnable.h \
    runnabletask.h \
    threadpool.h \
    workerthread.h

EXAMPLE_FILES += fileclient.html

