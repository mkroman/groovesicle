#-------------------------------------------------
#
# Project created by QtCreator 2011-09-17T15:53:11
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET    = Groovesicle
CONFIG   += link_pkgconfig
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

PKGCONFIG += QJson

SOURCES += main.cpp \
    Client.cpp \
    Request.cpp

HEADERS += \
    Client.hpp \
    Grooveshark.hpp \
    Request.hpp









