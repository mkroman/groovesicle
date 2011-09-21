#-------------------------------------------------
#
# Project created by QtCreator 2011-09-17T15:53:11
#
#-------------------------------------------------

QT       += network

TARGET = grooveshark
TEMPLATE = lib

windows: {
    INCLUDEPATH += ../../vendor/qjson/include
    LIBS += -L../../vendor/qjson/lib -lqjson
}

unix: {
    CONFIG += link_pkgconfig
    PKGCONFIG += QJson
}

SOURCES += Client.cpp \
    Request.cpp \
    Response.cpp

HEADERS += \
    Client.hpp \
    Grooveshark.hpp \
    Request.hpp \
    Response.hpp
