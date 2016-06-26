#-------------------------------------------------
#
# Project created by QtCreator 2015-02-10T13:04:44
#
#-------------------------------------------------

QT       += testlib xml

QT       -= gui

TARGET = tst_service
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    tst_template.cpp
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
    tst_template.h

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
