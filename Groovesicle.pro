#-------------------------------------------------
#
# Project created by QtCreator 2011-09-17T15:53:11
#
#-------------------------------------------------

QT       += core network
QT       -= gui

TARGET = Groovesicle
CONFIG   += link_pkgconfig console
CONFIG   -= app_bundle

TEMPLATE = app

windows: {
    INCLUDEPATH += ../vendor/qjson/include
    LIBS += -L../vendor/qjson/lib -lqjson
}

PKGCONFIG += QJson

SOURCES += main.cpp \
    Client.cpp \
    Request.cpp \
    Response.cpp

HEADERS += \
    Client.hpp \
    Grooveshark.hpp \
    Request.hpp \
    Response.hpp















