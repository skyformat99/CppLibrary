#-------------------------------------------------
#
# Project created by QtCreator 2015-02-10T13:04:44
#
#-------------------------------------------------

QT       += testlib xml

QT       -= gui

TARGET = tst_datatests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    testcontextobject1.cpp \
    testcontextobject2.cpp \
    tst_contextobject.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix {
    QMAKE_CXXFLAGS += -std=c++14
}

win32-g++: {
    QMAKE_CXXFLAGS += -std=c++14
}

DESTDIR=../

unix|win32: LIBS += -L$$PWD/../../lib/ -lData

INCLUDEPATH += $$PWD/../../lib/include/
DEPENDPATH += $$PWD/../../src/lib/

HEADERS += \
    testcontextobject1.h \
    testcontextobject2.h
