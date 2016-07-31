#-------------------------------------------------
#
# Project created by QtCreator 2015-02-10T13:02:30
#
#-------------------------------------------------

#QT       += xml

QT       -= gui

TARGET = ralph-simulation-data
TEMPLATE = lib

DEFINES += SIMULATION_DATA_LIBRARY

SOURCES += \
    simulationdescription.cpp \
    systemmapping.cpp \
    propertyvalue.cpp \
    effectmapping.cpp \
    effect.cpp \
    effectscript.cpp \
    scriptlibrary.cpp

HEADERS += \
    simulationdescription.h \
    systemmapping.h \
    propertyvalue.h \
    effectmapping.h \
    effect.h \
    effectscript.h \
    scriptlibrary.h

DESTDIR=../../lib
INCLUDEDIR = $${DESTDIR}/include/ralph/simulation/data/

unix|win32: LIBS += -L$$PWD/../../lib/ -lralph-data

INCLUDEPATH += $$PWD/../../lib/include/

unix {
    QMAKE_CXXFLAGS += -std=c++14
    target.path = /usr/lib
    INSTALLS += target

    QMAKE_POST_LINK += rm -fr $${INCLUDEDIR};
    QMAKE_POST_LINK += mkdir -p $${INCLUDEDIR};
    for(FILE, HEADERS){
        QMAKE_POST_LINK += cp $${PWD}/$${FILE} $${INCLUDEDIR};
    }
}

win32: {
    CONFIG += staticlib

    INCLUDEDIR ~= s,/,\\,g
    QMAKE_POST_LINK += rd $${INCLUDEDIR} /S /Q &
    QMAKE_POST_LINK += md $${INCLUDEDIR} &
    for(FILE, HEADERS){
        FILEPATH = $${PWD}/$${FILE}
        FILEPATH ~= s,/,\\,g
        QMAKE_POST_LINK += copy /y $${FILEPATH} $${INCLUDEDIR} &
    }
}

win32-g++: {
    QMAKE_CXXFLAGS += -std=c++14
}

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
