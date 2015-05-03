#-------------------------------------------------
#
# Project created by QtCreator 2015-02-10T13:02:30
#
#-------------------------------------------------

QT       += xml

QT       -= gui

TARGET = Data
TEMPLATE = lib

DEFINES += DATA_LIBRARY

SOURCES += \
    dataobject.cpp \
    datacontextmanager.cpp \
    datacontext.cpp \
    storagecontext.cpp \
    xmlstoragecontext.cpp \
    dataobjectfactory.cpp \
    contextobject.cpp \
    contextobjectfactory.cpp \
    xmldataserializer.cpp

HEADERS += data.h\
    data_global.h \
    dataobject.h \
    datacontextmanager.h \
    datacontext.h \
    dataexceptions.h \
    storagecontext.h \
    xmlstoragecontext.h \
    dataobjectfactory.h \
    contextobject.h \
    contextobjectfactory.h \
    textdataserializer.h \
    xmldataserializer.h

DESTDIR=../../../lib

unix {
    QMAKE_CXXFLAGS += -std=c++14
    target.path = /usr/lib
    INSTALLS += target

    INCLUDEDIR = $${DESTDIR}/include/Data/
    QMAKE_POST_LINK += rm -fr $${INCLUDEDIR};
    QMAKE_POST_LINK += mkdir -p $${INCLUDEDIR};
    for(FILE, HEADERS){
        QMAKE_POST_LINK += cp $${PWD}/$${FILE} $${INCLUDEDIR};
    }
}

win32: {
    CONFIG += staticlib

    INCLUDEDIR = $${DESTDIR}/include/Data/
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
