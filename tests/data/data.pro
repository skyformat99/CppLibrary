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
    testdataobject1.cpp \
    testdataobject2.cpp \
    tst_dataobject.cpp \
    tst_serializer.cpp \
    main.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix {
    QMAKE_CXXFLAGS += -std=c++14
}

win32-g++: {
    QMAKE_CXXFLAGS += -std=c++14
}

DESTDIR=../

unix|win32: LIBS += -L$$PWD/../../lib/ -lralph-data

INCLUDEPATH += $$PWD/../../lib/include/
DEPENDPATH += $$PWD/../../src/

HEADERS += \
    testdataobject1.h \
    testdataobject2.h \
    tst_dataobject.h \
    tst_serializer.h

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
