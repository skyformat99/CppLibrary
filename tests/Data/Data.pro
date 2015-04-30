#-------------------------------------------------
#
# Project created by QtCreator 2015-02-10T13:04:44
#
#-------------------------------------------------

QT       += testlib xml

QT       -= gui

TARGET = tst_datatest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_datatest.cpp \
    testdataobject1.cpp \
    testdataobject2.cpp
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
    testdataobject1.h \
    testdataobject2.h
